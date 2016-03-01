/*
 * edison_uart.cpp
 *
 *  Created on: 2016. 2. 26.
 *      Author: hwang
 */

#include "edison_uart.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(edison_uart)

edison_uart::edison_uart()
:cossb::interface::icomponent(COMPONENT(edison_uart)){
	// TODO Auto-generated constructor stub

}

edison_uart::~edison_uart() {
	// TODO Auto-generated destructor stub
}

bool edison_uart::setup()
{
	return true;
}

bool edison_uart::run()
{
	return true;
}

bool edison_uart::stop()
{
	return true;
}

void edison_uart::request(cossb::base::message* const msg)
{

}
