/**
 * @file		manager.hpp
 * @brief		COSSB component manager
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details
 */

#ifndef _COSSB_MANAGER_HPP_
#define _COSSB_MANAGER_HPP_

#include <map>
#include <vector>
#include <string>
#include <base/driver.hpp>
#include <arch/singleton.hpp>
#include <base/manifest.hpp>

using namespace std;

namespace cossb {
namespace base { template<class T> class libadopter; }
namespace interface {
	class ilog;
	class iauth;
}

namespace manager {

/**
 * @brief	component manager derived from singleton pattern
 */

class component_manager : public arch::singleton<component_manager> {
public:

	component_manager();
	virtual ~component_manager();

	component_manager(const component_manager&) = delete;
	component_manager& operator = (const component_manager&) = delete;

	/**
	 * @brief	install specific component
	 */
	bool install(const char* component_name);

	/**
	 * @brief	uninstall specific component
	 */
	bool uninstall(const char* component_name);
	bool uninstall();


	/**
	 * @brief run specific component
	 */
	bool run(const char* component_name);

	/**
	 * @brief run all components
	 */
	bool run();

	/**
	 * @brief	stop specific component
	 */
	bool stop(const char* component_name);

	/**
	 * @brief	stop all components
	 */
	bool stop();

	/**
	 * @brief	get count of the installed components
	 */
	int count();

	/**
	 * @brief	return specific component driver
	 */
	driver::component_driver* get_driver(const char* component_name);

};

#define cossb_component_manager		cossb::manager::component_manager::instance()

/**
 * @brief	system manager derived from singleton pattern
 */
class system_manager : public arch::singleton<system_manager> {

public:
	system_manager();
	virtual ~system_manager();

	system_manager(const system_manager&) = delete;
	system_manager& operator = (const system_manager&) = delete;

	/**
	 * @brief	setup system configuration
	 */
	bool setup(base::manifestreader* manifest);


private:

	/**
	 * @brief	dependent libraries adopter
	 */
	base::libadopter<interface::ilog>* _log_adopter = nullptr;

	/**
	 * @brief	authentication
	 */
	interface::iauth* _auth = nullptr;


};

#define cossb_system_manager	cossb::manager::system_manager::instance()


} /* namespace manager */
} /* namespace cossb */

#endif
