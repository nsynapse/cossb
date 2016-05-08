/*
 * wsclient.cpp
 *
 *  Created on: 2016. 4. 20.
 *      Author: hwang
 */

#include "wsclient.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(wsclient)

wsclient::wsclient()
:cossb::interface::icomponent(COMPONENT(wsclient)){
	// TODO Auto-generated constructor stub

}

wsclient::~wsclient() {
	// TODO Auto-generated destructor stub
}

bool serial::setup()
{

	return true;
}

bool serial::run()
{

	return true;
}

bool serial::stop()
{

	return true;
}

void serial::request(cossb::base::message* const msg)
{
\
}
