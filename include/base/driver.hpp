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


using namespace std;

namespace cossb {
namespace manager { class component_manager; }
namespace broker { class component_broker; }
namespace driver {

class component_driver {

	friend class manager::component_manager;
	friend class broker::component_broker;

public:
	component_driver(const char* component_path);
	virtual ~component_driver();

	/**
	 * @brief	component validation for driving
	 */
	bool valid();

	/**
	 * @brief	getting component pointer to access
	 */
	interface::icomponent* get_component() const { return _ptr_component; }

private:
	/**
	 * @brief	request message
	 */
	template<typename... Args>
	void request(const char* head, const Args&... args) {
		//not implemented.
	}

	void request(cossb::base::message* msg) {
		msg->serialize();
		_mailbox.push(msg);
		_condition.notify_one();
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
	 * @brief	read service description
	 */
	//void regist_service_desc();

	/**
	 * @brief	load component by name
	 */
	bool load(const char* component_name);

	/**
	 * @brief	unload component
	 */
	void unload();

	/**
	 * @brief	request process task
	 */
	void request_proc();

	/**
	 * for test, insert message
	 */
	template<typename... Args>
	void query(const char* head, const Args&... args) {

	}

	/**
	 * @brief	request
	 */
	base::task		_request_proc_task;


private:
	/**
	 * @brief	component impl.
	 */
	interface::icomponent* _ptr_component = nullptr;

	void* _handle = nullptr;

	/**
	 * @brief	mailbox
	 */
	std::queue<cossb::base::message*> _mailbox;

	boost::condition_variable _condition;
	boost::mutex _mutex;

};

} /* namespace driver */
} /* namespace cossb */

#endif
