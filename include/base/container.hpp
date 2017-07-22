/**
 * @file		container.hpp
 * @brief		component container class
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 6
 * @details	Component container
 */

#ifndef _COSSB_CONTAINER_HPP_
#define _COSSB_CONTAINER_HPP_

#include <string>
#include <map>
#include <interface/icomponent.hpp>
#include <arch/singleton.hpp>
#include <base/driver.hpp>

using namespace std;

namespace cossb {
namespace container {

typedef std::map<string, driver::component_driver*> comp_container;

class component_container : private arch::singleton<component_container> {

public:
	/**
	 * @brief	construct
	 */
	component_container() = default;

	/**
	 * @brief	destructor
	 */
	virtual ~component_container() { clear(); }

private:
	/**
	 * @brief	return size of the component container
	 */
	int size() { return _container.size(); }

	/**
	 * @brief	empty check
	 * @return	true, if the container is empty
	 */
	bool empty() { return _container.size()==0; }

	/**
	 * @brief	find component driver if it exists, and getting its driver
	 */
	driver::component_driver* get_driver(const char* component_name) {
		comp_container::iterator itr = _container.find(component_name);
		if(itr!=_container.end())
			return itr->second;
		else
			return nullptr;
	}

	/**
	 * @brief	add new component
	 * @return	true, if success
	 */
	bool add(const char* component_name, driver::component_driver* driver) {
		if(_container.find(component_name)==_container.end() && driver->valid()) {
			_container.insert(comp_container::value_type(component_name, driver));
			return true;
		}
		else {
			delete driver;
			driver = nullptr;
			return false;
		}
	}

	/**
	 * @brief	remove specific component
	 */
	bool remove(const char* component_name) {
		comp_container::iterator itr = _container.find(component_name);
		if(itr!=_container.end()) {
			if(itr->second) {
				delete itr->second;
				itr->second = nullptr;
			}
			//_container.erase(itr);
			return true;
		}
		return false;
	}

	/**
	 * @brief	check for component existence
	 */
	bool exist(const char* component_name) {
		if(_container.find(component_name)!=_container.end())
			return true;
		else
			return false;
	}

	/**
	 * @brief	clear all components
	 */
	void clear() {
		for(auto itr:_container) {
			if(itr.second) {
				delete itr.second;
				itr.second = nullptr;
			}
		}
		_container.clear();
	}


private:
	comp_container _container;

	friend class manager::component_manager;
};

#define cossb_component_container	cossb::container::component_container::instance()

} /* namespace container */
} /* namesapce cossb */



#endif /* _COSSB_CONTAINER_HPP_ */
