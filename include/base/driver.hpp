/**
 * @file		driver.hpp
 * @brief		Component driver
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details		Load components(shared library that support COSSB interface) and peripheral instances
 */

#ifndef _COSSB_DRIVER_HPP_
#define _COSSB_DRIVER_HPP_

#include <string>
#include <tuple>
#include <queue>
#include <base/interface.hpp>
#include <boost/any.hpp>
#include <base/message_any.hpp>


using namespace std;

namespace cossb {
namespace manager { class component_manager; }
namespace broker { class component_broker; }
namespace driver {

class component_driver {

	friend class manager::component_manager;
	friend class broker::component_broker;

public:
	component_driver(const char* component_name, int interval_ms);
	virtual ~component_driver();

	/**
	 * @brief	component validation for driving
	 */
	bool valid();

	/**
	 * @brief	getting component pointer to access
	 */
	interface::icomponent* get_component() const { return _ptr_component; }

	/*
	 * @brief	check component is mine
	 */
	bool mine(const char* component_name);

private:

	void subscribe(cossb::message* msg){
		boost::mutex::scoped_lock __lock(_mutex);
		_mailbox.push(*msg);
		__lock.unlock();

		_subscribe_cv.notify_one();
	}


	/**
	 * @brief	setup component
	 * @return	true, if success
	 */
	bool setup();

	/**
	 * @brief	run component
	 */
	bool run();

	/**
	 * @brief	stop component
	 */
	void stop();


private:

	/**
	 * @brief	load component by name
	 */
	bool load(const char* component_name);

	/**
	 * @brief	unload component
	 */
	void unload();

	/**
	 * @brief	subscribe process task
	 */
	void _subscribe_process();
	void _run_process();

	/**
	 * @brief	request task
	 */
	base::task	_subscribe_proc_task;
	base::task _run_proc_task;

private:
	/**
	 * @brief	component impl.
	 */
	interface::icomponent* _ptr_component = nullptr;

	void* _handle = nullptr;

	/**
	 * @brief	mailbox
	 */
	std::queue<cossb::message> _mailbox;

	boost::condition_variable _subscribe_cv;
	boost::condition_variable _run_cv;
	boost::mutex _mutex;
	int _interval_ms = 0;

};

} /* namespace driver */
} /* namespace cossb */

#endif
