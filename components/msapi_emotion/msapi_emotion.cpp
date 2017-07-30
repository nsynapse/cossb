/*
 * msapi_emotion.cpp
 *
 *  Created on: 2017. 7. 22.
 *      Author: hwang
 */

#include "msapi_emotion.hpp"
#include <cossb.hpp>
#include <curl/curl.h>
#include <opencv2/core.hpp>

USE_COMPONENT_INTERFACE(msapi_emotion)

msapi_emotion::msapi_emotion()
:cossb::interface::icomponent(COMPONENT(msapi_emotion)){

}

msapi_emotion::~msapi_emotion() {

}

bool msapi_emotion::setup()
{
	_request_url = get_profile()->get(profile::section::property, "url").asString("https://localhost");
	_key = get_profile()->get(profile::section::property, "key").asString("");


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
				try {
					cv::Mat image = boost::any_cast<cv::Mat>(*msg);

					//process

					//after process
					cossb::message _msg(this, base::msg_type::DATA);
					_msg.set((unsigned char)0x01);
					cossb_broker->publish("face_emotion", _msg);

					cossb_log->log(log::loglevel::INFO, "send message to spi");

					}
					catch(const boost::bad_any_cast&){
						cossb_log->log(log::loglevel::ERROR, "Invalid type casting..");
					}
			} break;
			case cossb::base::msg_type::RESPONSE: break;
			case cossb::base::msg_type::EVENT:  break;
			}
}

