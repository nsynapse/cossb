/*
 * edison_io.cpp
 *
 *  Created on: 2016. 2. 26.
 *      Author: hwang
 */

#include "edison_gpio.hpp"
#include <cossb.hpp>
#include <mraa.hpp>

USE_COMPONENT_INTERFACE(edison_gpio)

edison_gpio::edison_gpio()
:cossb::interface::icomponent(COMPONENT(edison_gpio)){

}

edison_gpio::~edison_gpio() {
	if(!_iomap.empty()) {
		for(map<int, mraa::Gpio*>::iterator itr = _iomap.begin(); itr!=_iomap.end(); ++itr) {
			if(itr->second) {
				delete itr->second;
			}
		}
	}
}

bool edison_gpio::setup()
{
	//set output port
	for(auto value: get_profile()->get(profile::section::property, "out")) {
		int port = value.asInt(-1);
		if(port>0) {
			_iomap.insert(std::pair<int, mraa::Gpio*>(port, new mraa::Gpio(port)));
			if(_iomap[port]!=nullptr)
				if(_iomap[port]->dir(mraa::DIR_OUT)!=mraa::SUCCESS)
					return false;
			else {
				cossb_log->log(log::loglevel::ERROR, "Unspecified GPIO Port");
				return false;
			}
		}
	}

	//set input port
	for(auto value: get_profile()->get(profile::section::property, "in")) {
		int port = value.asInt(-1);
		if(port>0) {
			_iomap.insert(std::pair<int, mraa::Gpio*>(port, new mraa::Gpio(port)));
			if(_iomap[port]!=nullptr)
				if(_iomap[port]->dir(mraa::DIR_IN)!=mraa::SUCCESS)
					return false;
			else {
				cossb_log->log(log::loglevel::ERROR, "Unspecified GPIO Port");
				return false;
			}
		}
	}

	return true;
}

bool edison_gpio::run()
{
	return true;
}

bool edison_gpio::stop()
{
	return true;
}

void edison_gpio::request(cossb::base::message* const msg)
{
	if(_iomap.empty()) {
		cossb_log->log(log::loglevel::ERROR, "No I/O configurations in profile. Check <property> in this component profile.");
		return;
	}

	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST: {
		if(!msg->get_frame()->topic.compare("service/gpio/write")) {
			cossb_log->log(log::loglevel::INFO, fmt::format("Received message (GPIO) : {}", msg->show().c_str()));
		}
	}
		break;
	case cossb::base::msg_type::DATA: break;
	default:
		cossb_log->log(log::loglevel::INFO, "Received message has unsupported type.");
	}


	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::DATA: { cossb_log->log(log::loglevel::INFO, fmt::format("Received : {}", msg->show()));} break;
	}
}

