/*
 * utlauncher.cpp
 *
 *  Created on: 2015. 9. 6.
 *      Author: hwang-linux
 */

#include "utilloader.hpp"
#include <dlfcn.h>
#include <popt.h>
#include <sys/stat.h>
#include "../logger.hpp"

namespace cossb {
namespace util {

utilloader::utilloader(const char* target_util) {
	if(!load(target_util))
		cossb_log->log(cossb::log::loglevel::INFO, fmt::format("Cannot load {} utility..", target_util).c_str());
}

utilloader::~utilloader() {
	unload();
}

bool utilloader::execute(int argc, char* argv[])
{
	if(_util_handle)
	{
		typedef bool(*util_execute)(int argc, char* argv[]);
		util_execute pf_execute = (util_execute)dlsym(_util_handle, "execute");
		if(!pf_execute) {
			dlclose(_util_handle);
			_util_handle = nullptr;
			return false;
		}

		pf_execute(argc, argv);

		return true;
	}

	return false;
}

bool utilloader::load(const char* target_util)
{
	_util_handle = dlopen(fmt::format("./{}.util",target_util).c_str(), RTLD_LAZY|RTLD_GLOBAL);
	if(_util_handle)
		return true;

	return false;
}


void utilloader::unload()
{
	if(_util_handle)
	{
		dlclose(_util_handle);
		_util_handle = nullptr;
		cossb_log->log(cossb::log::loglevel::INFO, "Unload utility..");
	}
}

} /* namespace util */
} /* namespace cossb */
