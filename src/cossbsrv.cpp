/*
 * @brief	cossb entry for linux service
 * @author	Byunghun Hwang <elecun2@gmail.com>
 */

#include <iostream>
#include <csignal>
#include <cstdlib>
#include <ext/cxxopts.hpp>
#include <memory>
#include <dirent.h>
#include <unistd.h>
#include <cossb.hpp>

#include <syslog.h>


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
int main(void)
{

	pid_t pid, sid;

	pid = fork();
	if(pid<0) exit(EXIT_FAILURE); //failed
	if(pid>0) exit(EXIT_SUCCESS); //return a child pid

	umask(0);

	sid = setsid();
	if (sid < 0) {
			/* Log the failure */
			exit(EXIT_FAILURE);
	}

	signal(SIGINT, sigc_interrupt);

	try {
		signal(SIGINT, sigc_interrupt); //considering use sigaction function.

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

