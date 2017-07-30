/*
 * msapi_emotion.cpp
 *
 *  Created on: 2017. 7. 22.
 *      Author: hwang
 */

#include "msapi_emotion.hpp"
#include <cossb.hpp>
#include <curl/curl.h>

USE_COMPONENT_INTERFACE(msapi_emotion)

msapi_emotion::msapi_emotion()
:cossb::interface::icomponent(COMPONENT(msapi_emotion)){

}

msapi_emotion::~msapi_emotion() {

}

bool msapi_emotion::setup()
{

	return true;
}

bool msapi_emotion::run()
{
	return true;
}

bool msapi_emotion::stop()
{
	return true;
}

void msapi_emotion::request(cossb::message* const msg)
{
	switch(msg->get_frame()->type) {
			case cossb::base::msg_type::REQUEST: break;
			case cossb::base::msg_type::DATA: {
			} break;
			case cossb::base::msg_type::RESPONSE: break;
			case cossb::base::msg_type::EVENT:  break;
			}
}

