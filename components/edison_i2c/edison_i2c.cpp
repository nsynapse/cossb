/*
 * edison_i2c.cpp
 *
 *  Created on: 2016. 2. 26.
 *      Author: hwang
 */

#include "edison_i2c.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(edison_i2c)

edison_i2c::edison_i2c()
:cossb::interface::icomponent(COMPONENT(edison_i2c)){
	// TODO Auto-generated constructor stub

}

edison_i2c::~edison_i2c() {
	// TODO Auto-generated destructor stub
}

bool edison_i2c::setup()
{
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
