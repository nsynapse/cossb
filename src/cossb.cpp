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
 * @file		cossb.cpp
 * @brief		COSS Broker application
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 9
 * @details		COSSB Application
 */

#include <iostream>
#include <csignal>
#include <cstdlib>
#include <ext/cxxopts.hpp>
#include <memory>
#include <dirent.h>
#include <unistd.h>
#include <cossb.hpp>

using namespace std;

void terminate() {
	cossb::core::destroy();
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
 * @param	arguments
 * @details	Start with default components
 */
int main(int argc, char* argv[])
{
	signal(SIGINT, sigc_interrupt);

	try {
		signal(SIGINT, sigc_interrupt);

		cxxopts::Options options(argv[0], "CommandLine Options");
		options.add_options()
			("r,run", "Manifest File(*.xml)", cxxopts::value<std::string>(), "FILE")
			("v,version", "Print Version")
			("h,help", "Print Help");

		options.parse(argc, argv);

		//Options
		if(options.count("help")){ std::cout << options.help({ "", "Group" }) << std::endl; exit(0);}
		else if(options.count("v")){ std::cout << COSSB_NAME << COSSB_VERSION << " (Built " << __DATE__ << " " <<__TIME__ << ")" << std::endl;	exit(EXIT_SUCCESS); }
		else if(options.count("r"))
		{
			auto& file = options["r"].as<std::string>();
			cossb_log->log(log::loglevel::INFO, fmt::format("{}{} Now Starting....",COSSB_NAME, COSSB_VERSION).c_str());

			if(!cossb::core::init(file.c_str()))
				::terminate();

			cossb::core::start();
			pause();
		}
		else{ std::cout << options.help({ "", "Group" }) << std::endl; exit(0);}
	}
	catch(const cxxopts::OptionException& e) {
		std::cout << "error parsing options : " << e.what() << std::endl;
		exit(1);
	}

	::terminate();

	return 0;
}
