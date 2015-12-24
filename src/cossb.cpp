/**
Copyright (c) 2015, Nsynapse Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @mainpage	COSSB(Component-based Open & Simple Service Broker)
 * @details
 */


/**
 * @file		cossb.cpp
 * @brief		COSS Broker application
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 9
 * @details		COSSB Application
 */

#include <iostream>
#include <csignal>
#include <cstdlib>
#include <popt.h>
#include <memory>
#include <dirent.h>
#include <unistd.h>
#include <cossb.hpp>

using namespace std;
using namespace cossb;

void terminate() {
	core::destroy();
	exit(EXIT_SUCCESS);
}

/**
 * @brief	SIGINT signal callback function
 * @details	Stop all services and destroy all instances
 */
void sigc_interrupt(int param) {
	::terminate();
}

/**
 * @brief	Main routine
 * @param	command
 * @details	Start with default components
 */
int main(int argc, char* argv[])
{
	signal(SIGINT, sigc_interrupt);

	char* manifest_file = nullptr;
	struct poptOption optionTable[] =
	{
		{"run",			'r', POPT_ARG_STRING, (void*)manifest_file, 'r', "Run Broker with manifest file", "*.xml manifest file"},
		{"version",		'v', POPT_ARG_NONE, 0, 'v', "Show COSSB Version", "version"},
		POPT_AUTOHELP
		POPT_TABLEEND
	};
	poptContext optionCon = poptGetContext(NULL, argc, (const char**)argv, optionTable, 0);
	poptSetOtherOptionHelp(optionCon, "<option>");

	if(argc<2)
	{
		std::cout << poptStrerror(POPT_ERROR_NOARG) << endl;
		exit(EXIT_SUCCESS);
	}

	//only one opt
	int opt = poptGetNextOpt(optionCon);
	if(opt>=0)
	{
		switch(opt)
		{
		/* run with manifest file */
		case 'r': {
			cossb_log->log(log::loglevel::INFO, fmt::format("{}{} Now Starting....",COSSB_NAME, COSSB_VERSION).c_str());

			if(!core::init((const char*)poptGetOptArg(optionCon)))
				::terminate();

			core::start();
			pause();

		} break;

		/* show cossb version */
		case 'v':{ std::cout << COSSB_NAME << COSSB_VERSION << " (Built " << __DATE__ << " " <<__TIME__ << ")" << std::endl;	exit(EXIT_SUCCESS); } break;
		}
	}

	if (opt<-1)
	{
		cout << poptBadOption(optionCon, POPT_BADOPTION_NOALIAS) << ":" << poptStrerror(opt) << endl;
		::terminate();
	}

	poptFreeContext(optionCon);

	::terminate();

	return 0;
}
