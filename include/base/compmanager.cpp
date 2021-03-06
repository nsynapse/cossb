/**
 * @file		compmanager.cpp
 * @brief		COSSB component manager
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details		management for all service component installation
 */

#include "manager.hpp"
#include <base/container.hpp>
#include <base/driver.hpp>
#include <base/broker.hpp>
#include <base/log.hpp>
#include <base/manifest.hpp>
#include <base/exception.hpp>
#include <base/common.hpp>
#include <list>
#include <base/manifest.hpp>

using namespace std;

namespace cossb {
namespace manager {

component_manager::component_manager()
{

}

component_manager::~component_manager()
{
	stop();
	uninstall();
}

bool component_manager::install(const char* component_name)
{
	if(!component_name)
		return false;

	if(cossb_component_container->exist(component_name)){
		cossb_log->log(log::loglevel::WARN, fmt::format("Already installed <{}>", component_name));
		return false;
	}

	cossb_log->log(log::loglevel::INFO, fmt::format("Install <{}>", component_name));

	if(cossb_component_container->add(component_name, new driver::component_driver(component_name, -1)))
	{
		driver::component_driver* driver = cossb_component_container->get_driver(component_name);

		for(auto srv:driver->get_component()->get_profile()->_services)
			cossb_broker->regist(&srv);

		if(driver->setup())
			return true;
	}

	this->uninstall(component_name);

	return false;
}

bool component_manager::uninstall(const char* component_name)
{
	if(cossb_component_container->exist(component_name))
	{
		cossb_component_container->get_driver(component_name)->stop();
		cossb_component_container->remove(component_name);
		cossb_log->log(log::loglevel::INFO, fmt::format("Uninstall <{}>", component_name));
		return true;
	}
	return false;
}

bool component_manager::uninstall()
{
	for(auto comp:cossb_component_container->_container) {
		this->uninstall(comp.first.c_str());
	}
	cossb_component_container->clear();
	return true;
}


bool component_manager::run(const char* component_name)
{
	if(cossb_component_container->exist(component_name))
	{
		cossb_log->log(log::loglevel::INFO, fmt::format("Run <{}>", component_name));
		return cossb_component_container->get_driver(component_name)->run();
	}
	return false;
}

bool component_manager::run()
{
	for(auto comp:cossb_component_container->_container) {
		this->run(comp.first.c_str());
	}
	return true;
}

bool component_manager::stop(const char* component_name)
{
	if(cossb_component_container->exist(component_name)) {
		cossb_component_container->get_driver(component_name)->stop();
		cossb_log->log(log::loglevel::INFO, fmt::format("Stopped <{}>", component_name));
		return true;
	}
	return false;
}

bool component_manager::stop()
{
	for(auto comp:cossb_component_container->_container) {
		this->stop(comp.first.c_str());
	}
	return true;
}

int component_manager::count()
{
	return cossb_component_container->_container.size();
}

driver::component_driver* component_manager::get_driver(const char* component_name)
{
	if(cossb_component_container->exist(component_name)) {
		return cossb_component_container->get_driver(component_name);
	}
	return nullptr;
}

} /* namespace manager */
} /* namespace cossb */
