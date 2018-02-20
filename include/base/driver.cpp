/**
 * @file		driver.cpp
 * @brief		Component driver
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load components with driver
 */

#include "driver.hpp"
#include <dlfcn.h>
#include <iostream>
#include <base/profile.hpp>
#include <tuple>
#include <base/broker.hpp>
#include <base/exception.hpp>
#include <util/format.h>
#include <base/log.hpp>
#include <base/manifest.hpp>
#include <base/common.hpp>

using namespace std;
using namespace cossb;

namespace cossb {
namespace driver {

component_driver::component_driver(const char* component_name, int interval_ms=-1)
:_interval_ms(interval_ms)
{
	try {
		string comp_dir = cossb_manifest->get_path()[__COMPONENT__];
		if(comp_dir.empty())
			comp_dir = "./";

		if(load((comp_dir+string(component_name)).c_str()))
		{
			string profile_path = fmt::format("{}{}{}",comp_dir,component_name,__PROFILE_EXT__);

			if(_ptr_component) {
				_ptr_component->_profile = new profile::xml();
				if(!_ptr_component->_profile->load(_ptr_component, profile_path.c_str())){
					unload();
				}
			}
		}
		else
			throw exception(excode::COMPONENT_LOAD_FAIL);
	}
	catch(driver::exception& e) {
		cossb_log->log(log::loglevel::ERROR, fmt::format("<{}> : {}", component_name, e.what()));
	}
}

component_driver::~component_driver()
{
	try {
		unload();
	}
	catch(driver::exception& e) {
		cossb_log->log(log::loglevel::ERROR, e.what());
	}
}

bool component_driver::load(const char* component_path)
{
	string fullpath = fmt::format("{}{}",component_path, __COMPONENT_EXT__);

	_handle = dlopen(fullpath.c_str(), RTLD_LAZY|RTLD_GLOBAL);

	if(_handle)
	{
		create_component pfcreate = (create_component)dlsym(_handle, "create");
		if(!pfcreate)
		{
			dlclose(_handle);
			_handle = nullptr;

			return false;
		}

		_ptr_component = pfcreate();
		return true;
	}
	else
		throw exception(excode::COMPONENT_CREATE_FAIL);

	return false;
}

void component_driver::unload()
{
	if(_ptr_component)
	{
		destroy_component pfdestroy = (destroy_component)dlsym(_handle, "destroy");

		if(_subscribe_proc_task.get())
			destroy_task(_subscribe_proc_task);

		if(pfdestroy) {
			pfdestroy();
		}
		else
			throw exception(excode::COMPONENT_UNLOAD_FAIL);

		_ptr_component = nullptr;
	}

	if(_handle)
	{
		dlclose(_handle);
		_handle = nullptr;
	}
}

bool component_driver::setup()
{
	if(_ptr_component) {
		_interval_ms = _ptr_component->get_profile()->get(profile::section::property, "interval").asInt(-1);
		return _ptr_component->setup();
	}

	return false;
}

bool component_driver::run()
{
	if(_ptr_component){
		if(!_subscribe_proc_task.get()){
			_subscribe_proc_task = create_task(component_driver::_subscribe_process);
			return true;
		}
	}
	return false;
}

void component_driver::stop()
{
	if(_ptr_component)
		_ptr_component->stop();

	_subscribe_cv.notify_one();

	if(_subscribe_proc_task.get())
		destroy_task(_subscribe_proc_task);
}

void component_driver::_subscribe_process()
{
	if(_ptr_component) {
		while(1){
			try {
				if(_interval_ms<0){
					cossb::message msg;
					_mailbox.wait_pop(msg);
					//_ptr_component->subscribe(&msg);
				}
				else{
					_ptr_component->run();
					if(_subscribe_proc_task->interruption_requested()) break;
					boost::this_thread::sleep(boost::posix_time::milliseconds(_interval_ms));
				}
			}
			catch(thread_interrupted&) {
				break;
			}
		}
	}
}

bool component_driver::valid()
{
	return _handle!=nullptr;
}

bool component_driver::mine(const char* component_name)
{
	if(!string(_ptr_component->get_name()).compare(component_name))
		return true;
	return false;
}



} /* namespace dirver */
} /* namespace cossb */
