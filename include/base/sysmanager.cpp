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
#include <base/common.hpp>

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

	//pre-load component/library/package
	for(auto dep:manifest->get_required()) {
		switch(dep->type) {
		case base::bundleType::PACKAGE:
			//code here for packages
			break;
		case base::bundleType::COMPONENT:
			cossb_component_manager->install(dep->name.c_str());
			break;
		case base::bundleType::LIBRARY:
			//code here for libraries
			break;
		}
	}

	return true;
}

} /* namespace manager */
} /* namespace cossb */
