/*
 @file queue_safe.hpp
 @author		Byunghun Hwang<bhhwang@dgist.ac.kr>
 @brief		Thread Safe Standard Queue container
 */

#ifndef _COSSB_UTIL_QUEUE_SAFE_
#define _COSSB_UTIL_QUEUE_SAFE_

#include <queue>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;

namespace cossb {
	namespace util {
		template<typename _T>
		class queue_safe {
		public:

			/*
			 @brief	push
			 */
			void push(_T const& data){
				boost::mutex::scoped_lock _lock(_mutex);
				_queue.push(data);
				_lock.unlock();
				_condition.notify_one();
			}

			void clear_push(_T const& data) {
				boost::mutex::scoped_lock _lock(_mutex);
				std::swap(_queue, queue<_T>());
				_queue.push(data);
				_lock.unlock();
				_condition.notify_one();
			}

			bool empty() const
			{
				boost::mutex::scoped_lock _lock(_mutex);
				return _queue.empty();
			}

			bool pop(_T& data) {
				boost::mutex::scoped_lock _lock(_mutex);
				if (_queue.empty())
					return false;
				data = _queue.front();
				_queue.pop();
				return true;
			}

			void wait_pop(_T& data) {
				boost::mutex::scoped_lock _lock(_mutex);
				while (_queue.empty())
					_condition.wait(_lock);
				data = _queue.front();
				_queue.pop();
			}

			void wait_pop_back(_T& data) {
				boost::mutex::scoped_lock _lock(_mutex);
				while (_queue.empty())
					_condition.wait(_lock);
				data = _queue.back();
				while(!_queue.empty())
					_queue.pop();
				//std::swap(_queue, queue<_T>());
			}

			int size() {
				return (int)_queue.size();
			}

			void clear() {
				boost::mutex::scoped_lock _lock(_mutex);
				std::swap(_queue, queue<_T>());
			}

		private:
			std::queue<_T> _queue;
			mutable boost::mutex _mutex;
			boost::condition_variable _condition;

		};
	} /* namespace util */
} /* namespace cossb */




#endif /* _COSSB_UTIL_QUEUE_SAFE_ */
