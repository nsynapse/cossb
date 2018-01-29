
/**
@file	taskDriver.hpp
@brief	Task Driver Class
@author	Byunghun Hwang <bhhwang@dgist.ac.kr>
*/

#ifndef __COMMON_ARCH_TASK_DRIVER__
#define __COMMON_ARCH_TASK_DRIVER__

#include <common/base/abstract/iTask.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/bind.hpp>
#include <queue>
#include <mutex>
#include <utils\safeQueue.hpp>

using namespace std;

namespace dgist { namespace arch { class taskManager; } }
namespace dgist {
	namespace arch {

		/**
		@class	taskDriver
		@brief
		task manager can drive a task via driver.
		So, all task impl. class does not have a thread directly.
		*/
		class taskDriver {

			friend class dgist::arch::taskManager;

		public:

			/**
			@brief	task driver class constructor
			@param
			taskname	task name to identify the task
			task		task imple. class instance pointer
			interval_ms	time interval between steps, if you does not want to run intervally, set -1.
			*/
			taskDriver(const char* taskname, dgist::abstract::iTask* task, unsigned int interval_ms = -1) :_ptr_task(task), _interval_ms(interval_ms) {
				task->setStatus(abstract::iTask::TASK_STATUS::STOPPED);
			}
			virtual ~taskDriver() {
				if (_ptr_task)
					_ptr_task->stop();

				_safe_mailbox.clear();
			}

			/**
			@brief	interface function to request
			@return	none
			@param	any type of data
			*/
			void request(boost::any& data) {
				if (data.empty())
					return;

				if (_ptr_task->getStatus() == dgist::abstract::iTask::TASK_STATUS::STOPPED)
					return;

				//!!only dependent task can be requested.
				//no use of mutex for test (bhhwnag, 11/30)
				if (_interval_ms < 0) {
					//std::unique_lock<boost::mutex> lock(_mutex);
					//_condition.wait(lock, [this]() { return _mailbox.empty();  });
					//_mailbox.push(data);
					_safe_mailbox.push(data);
					//lock.unlock();
					//_condition.notify_one();
				}
			}

			/*
			@brief	return mailbox size
			*/
			int size() {
				return (int)_safe_mailbox.size();
			}

		private:
			/**
			@brief	start to run the task
			@param	none
			@return	none
			@remark
			create own thread
			the thread will call your run function continuously
			*/
			void run() {
				if (_ptr_task) {
					if (!_task.get() && _ptr_task->getStatus()==dgist::abstract::iTask::TASK_STATUS::STOPPED) {
						_task = boost::shared_ptr<boost::thread>(new boost::thread(&dgist::arch::taskDriver::_proc, this));
						_ptr_task->setStatus(dgist::abstract::iTask::TASK_STATUS::RUNNING);
					}
				}
			}

			/**
			@brief	stop the task
			@param	none
			@return	none
			@remark
			interrupt the thread, wait until close the thread
			stop function in your class will be called.
			*/
			void stop() {
				if (_ptr_task) {
					_ptr_task->stop();
					_ptr_task->setStatus(dgist::abstract::iTask::TASK_STATUS::STOPPED);
				}
				_condition.notify_one();
				if (_task.get()) {
					_task->interrupt();
					_task->join();
					_task.reset();
				}
			}

			/**
			@brief	setup the task (initialize)
			@param	none
			@return	none
			@remark	setup function in your task class will be called.
			*/
			void setup() {
				if (_ptr_task)
					_ptr_task->setup();
			}

			/*
			@breif	reset the task (reinitialize)
			*/
			void reset() {
				if (_ptr_task) {
					this->stop();
					_safe_mailbox.clear();
					//std::swap(_mailbox, queue<boost::any>());
					_ptr_task->reset();
					//this->run();
				}
			}

			/**
			@brief	task process function
			@param	none
			@return	none
			@remark
			*/
			void _proc() {
				if (_ptr_task) {
					while (1) {
						try {
							//for dependent task
							if (_interval_ms < 0) {
								boost::any data;
								_safe_mailbox.wait_pop_back(data);
								_ptr_task->request(&data);

								/*boost::mutex::scoped_lock __lock(_mutex);
								while (_mailbox.empty())
									_condition.wait(__lock);

								int size = (int)_mailbox.size();
								for (int i = 0; i < size; i++) {
									_ptr_task->request(&_mailbox.front());
									_mailbox.pop();
								}*/
								/*while (!_mailbox.empty()) {
									_ptr_task->request(&_mailbox.front());
									_mailbox.pop();
								}*/
							}
							else {
								_ptr_task->run();
								if (_task->interruption_requested()) break;
								boost::this_thread::sleep(boost::posix_time::milliseconds(_interval_ms));
							}
						}
						catch (boost::thread_interrupted&) {
							break;
						}
					}
				}
			}

			/*
			@brief	return the task status
			*/
			/*dgist::abstract::iTask::TASK_STATUS getStatus() {
				return _ptr_task->getStatus();
			}*/

		private:
			boost::shared_ptr<boost::thread> _task = nullptr;
			dgist::abstract::iTask* _ptr_task = nullptr;
			boost::condition _condition;
			boost::mutex _mutex;
			int _interval_ms = 0;
			//queue<boost::any> _mailbox;
			utils::safeQueue<boost::any> _safe_mailbox;

		};
	} /* namespace arch */
} /* namespace dgist */

#endif
