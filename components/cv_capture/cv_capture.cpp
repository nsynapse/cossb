/*
 * cv_capture.cpp
 *
 *  Created on: 2017. 7. 22.
 *      Author: hwang
 */

#include "cv_capture.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(cv_capture)

cv_capture::cv_capture()
:cossb::interface::icomponent(COMPONENT(cv_capture)){

}

cv_capture::~cv_capture() {

}

bool cv_capture::setup()
{


	return true;
}

bool cv_capture::run()
{
	return true;
}

bool cv_capture::stop()
{
	return true;
}

void cv_capture::request(cossb::message* const msg)
{

}

