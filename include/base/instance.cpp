

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

	//1. load manifest file
	if(!cossb_manifest->load(manifest_file))
		return false;

	//2. authentication


	//3. setting up by manifest
	if(setup) {
		if(!cossb_system_manager->setup(cossb_manifest))
			return false;
	}

	return true;
}

void destroy()
{
	cossb_log->log(log::loglevel::INFO, "Now terminating...");
	cossb_broker->destroy();
	cossb_system_manager->destroy();
	cossb_manifest->destroy();
}

bool sync()
{
	return true;
}


bool start()
{
	cossb_log->log(log::loglevel::INFO, "Now all components is running...");
	if(cossb_component_manager->run())
		return true;

	return false;
}

bool stop()
{
	if(cossb_component_manager->count()>0)
	{
		cossb_log->log(log::loglevel::INFO, "Now all components is stopping...");
		if(cossb_component_manager->stop())
			return true;
	}

	return true;
}



} /* namespace core */
} /* namespace cossb */
