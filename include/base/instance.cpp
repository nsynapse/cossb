

#include "instance.hpp"
#include <base/manifest.hpp>
#include <base/manager.hpp>
#include <base/broker.hpp>
#include <base/log.hpp>
#include <string>
#include <iostream>


using namespace std;

namespace cossb {
namespace core {

bool init(const char* manifest_file, bool setup)
{

	//1. load manifest file(must run first)
	if(!cossb_manifest->load(manifest_file))
		return false;

	//2. setting up by manifest (all requirements will be checked)
	if(setup) {
		if(!cossb_system_manager->setup(cossb_manifest))
			return false;
	}

	return true;
}

void destroy()
{
	cossb_broker->destroy();
	cossb_system_manager->destroy();
	cossb_manifest->destroy();
}


bool start()
{
	if(cossb_component_manager->run())
		return true;

	return false;
}

bool stop()
{
	if(cossb_component_manager->count()>0)
	{
		if(cossb_component_manager->stop())
			return true;
	}

	return true;
}



} /* namespace core */
} /* namespace cossb */
