/**
 * @file		sysmanager.cpp
 * @brief		COSSB system manager
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 7. 29
 * @details
 */

#include "manager.hpp"
#include <base/log.hpp>
#include <base/libadopter.hpp>
#include <secure/auth.hpp>

namespace cossb {
namespace manager {

system_manager::system_manager()
{

}

system_manager::~system_manager()
{
	cossb_component_manager->destroy();
	cossb_log->destroy();

	if(_log_adopter)	delete _log_adopter;
}

bool system_manager::setup(base::manifestreader* manifest)
{
	if(!manifest)
		return false;

	//1. authentication
	if(!cossb_auth->authentication(manifest))
		return false;

	if(!manifest->is_enabled("auth"))
		return false;


	//pre-load package after loading libraries
	for(auto dep:manifest->get_required()) {
		if(dep->type==base::bundleType::PACKAGE) {

		}
	}

	//pre-load components after loading libraries
	for(auto dep:manifest->get_required()) {
		string prefix = manifest->get_path()["component"];
		if(prefix.empty()) prefix = "./";

		if(dep->type==base::bundleType::COMPONENT) {
			cossb_component_manager->install((prefix+dep->name).c_str());
		}
	}

	return true;
}

} /* namespace manager */
} /* namespace cossb */
