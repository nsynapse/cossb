/*
 * edison_i2c.cpp
 *
 *  Created on: 2016. 2. 26.
 *      Author: hwang
 */

#include "edison_i2c.hpp"
#include <cossb.hpp>
#include <mraa.hpp>

USE_COMPONENT_INTERFACE(edison_i2c)

edison_i2c::edison_i2c()
:cossb::interface::icomponent(COMPONENT(edison_i2c)){
	// TODO Auto-generated constructor stub

}

edison_i2c::~edison_i2c() {
	if(!_addressmap.empty()) {
		for(map<unsigned char, mraa::I2c*>::iterator itr = _addressmap.begin(); itr!=_addressmap.end(); ++itr) {
			if(itr->second) {
				delete itr->second;
			}
		}
	}
}

bool edison_i2c::setup()
{
	//set address
	for(auto value: get_profile()->get(profile::section::property, "address")) {
		unsigned char address = value.asUChar(0x00);
		if(address!=0x00) {
			_addressmap.insert(std::pair<unsigned char, mraa::I2c*>(address, new mraa::I2c(0)));
			if(_addressmap[address]->address(address)!=mraa::Result::SUCCESS)
				return false;
			else
				cossb_log->log(log::loglevel::INFO, fmt::format("Set I2C Address : {}", value.asString("")));
		}
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

}