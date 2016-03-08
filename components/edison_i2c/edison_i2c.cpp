/*
 * edison_i2c.cpp
 *
 *  Created on: 2016. 2. 26.
 *      Author: hwang
 */

#include "edison_i2c.hpp"
#include <cossb.hpp>
#include <mraa.hpp>
#include <algorithm>

USE_COMPONENT_INTERFACE(edison_i2c)

edison_i2c::edison_i2c()
:cossb::interface::icomponent(COMPONENT(edison_i2c)){
	// TODO Auto-generated constructor stub

}

edison_i2c::~edison_i2c() {
	if(_i2c)
		delete _i2c;
}

bool edison_i2c::setup()
{
	if(!_i2c)
		_i2c = new mraa::I2c(0);

	//set address
	for(auto value: get_profile()->get(profile::section::property, "address")) {
		int address = value.asInt(0);
		address += ((address/16)+1)*6;
		cossb_log->log(log::loglevel::INFO, fmt::format("Set I2C Address : 0x{0:x}", address));

		if(address) {
			if(_i2c->address(address)!=mraa::Result::SUCCESS)
				return false;
			else
				cossb_log->log(log::loglevel::INFO, fmt::format("Set I2C Address : {}", value.asString("")));
			break;
		}
	}

	//set mode
	for(auto mode: get_profile()->get(profile::section::property, "mode")) {
		string m = mode.asString("");
		std::transform(m.begin(), m.end(), m.begin(), ::tolower);
		if(m.compare("i2c_std")==0)	_i2c->frequency(mraa::I2cMode::I2C_STD);	//up to 100khz
		else if(m.compare("i2c_high")==0)	_i2c->frequency(mraa::I2cMode::I2C_HIGH); //up to 3.4Mhz
		else if(m.compare("i2c_fast")==0)	_i2c->frequency(mraa::I2cMode::I2C_FAST);//up to 400khz
	}
	return true;
}

bool edison_i2c::run()
{
	return true;
}

bool edison_i2c::stop()
{
	return true;
}

void edison_i2c::request(cossb::base::message* const msg)
{
	if(!_i2c) {
		cossb_log->log(log::loglevel::ERROR, "No I2C Device");
		return;
	}

	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST: {
		if(!msg->get_frame()->topic.compare("service/i2c/write")) {
			cossb_log->log(log::loglevel::INFO, fmt::format("Received message (I2C) : {}", msg->show().c_str()));
		}
	}
		break;
	case cossb::base::msg_type::DATA: break;
	default:
		cossb_log->log(log::loglevel::INFO, "Received message has unsupported type.");
	}

}
