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
#include <base/log.hpp>
#include <base/manifest.hpp>
#include <base/exception.hpp>
#include <list>

using namespace std;

namespace cossb {
namespace manager {

component_manager::component_manager()
{

}

component_manager::~component_manager()
{
	stop();
	cossb_component_container->destroy();
}

bool component_manager::install(const char* component_name)
{
	string component_path = cossb_manifest->get_path()["component"];
	if(component_path.empty())
		component_path = "./"+string(component_name);
	else
		component_path+=component_name;

	if(cossb_component_container->add(component_name, new driver::component_driver(component_path.c_str())))
	{
		cossb_log->log(log::loglevel::INFO, fmt::format("Component installed : {}", component_name).c_str());
		cossb_component_container->get_driver(component_name)->setup();
		return true;
	}

	return false;
}

bool component_manager::uninstall(const char* component_name)
{
	if(cossb_component_container->exist(component_name))
	{
		cossb_component_container->get_driver(component_name)->stop();
		cossb_component_container->remove(component_name);
		cossb_log->log(log::loglevel::INFO, fmt::format("Component uninstalled : {}", component_name).c_str());
		return true;
	}
	return false;
}


bool component_manager::run(const char* component_name)
{
	if(cossb_component_container->exist(component_name))
	{
		cossb_component_container->get_driver(component_name)->run();
		return true;
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
