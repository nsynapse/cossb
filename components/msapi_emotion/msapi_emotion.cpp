/*
 * msapi_emotion.cpp
 *
 *  Created on: 2017. 7. 22.
 *      Author: hwang
 */

#include "msapi_emotion.hpp"
#include <cossb.hpp>
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

	//1. initialize
	curl_global_init(CURL_GLOBAL_ALL) ;
	_ctx = curl_easy_init();

	if(_ctx==nullptr){
		cossb_log->log(log::loglevel::ERROR, "Curl cannot be initialized.");
		return false;
	}

	curl_slist* header = nullptr;
	header = curl_slist_append(header, "Host: westcentralus.api.cognitive.microsoft.com");
	header = curl_slist_append(header, fmt::format("Ocp-Apim-Subscription-Key:{}",_key).c_str());
	header = curl_slist_append(header , "Content-Type: application/json" ) ;
	curl_easy_setopt(_ctx , CURLOPT_HTTPHEADER , header);
	curl_easy_setopt(_ctx , CURLOPT_NOPROGRESS , 1);
	curl_easy_setopt(_ctx , CURLOPT_URL,  _request_url);
	curl_easy_setopt(_ctx, CURLOPT_POSTFIELDS, "returnFaceAttributes=emotion");



	return true;
}

bool msapi_emotion::run()
{
	//1. perform
	CURLcode res = curl_easy_perform(_ctx);

	if(res!=CURLE_OK) {
		cossb_log->log(log::loglevel::INFO, fmt::format("curl perform fail : {}",_request_url));
		cossb_log->log(log::loglevel::ERROR, fmt::format("curl perform fail : {}",curl_easy_strerror(res)));
	}
	else{
		string data;
		curl_easy_setopt(_ctx, CURLOPT_WRITEDATA, &data);
		cossb_log->log(log::loglevel::ERROR, data);
	}

	return true;
}

bool msapi_emotion::stop()
{
	curl_easy_cleanup(_ctx);
	curl_global_cleanup();
	return true;
}

void msapi_emotion::subscribe(cossb::message* const msg)
{
	cossb_log->log(log::loglevel::INFO, "(emotion)received message");

	switch(msg->get_frame()->type) {
			case cossb::base::msg_type::REQUEST: break;
			case cossb::base::msg_type::DATA: {
				try {
					cv::Mat image = boost::any_cast<cv::Mat>(*msg->get_data());
					//process

					//after process
//					cossb::message _msg(this, base::msg_type::DATA);
//					_msg.set((unsigned char)0x01);
//					cossb_broker->publish("face_emotion", _msg);

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

void msapi_emotion::get_post_data(std::ostringstream& postBuf, const char** pp)
{
	while(*pp!=nullptr)
	{
			// curl_escape( {string} , 0 ): replace special characters
			// (such as space, "&", "+", "%") with HTML entities.
			// ( 0 => "use strlen to find string length" )
			// remember to call curl_free() on the strings on the way out
			char* key = curl_escape( pp[0] , 0 );
			char* val = curl_escape( pp[1] , 0 );

			postBuf << key << "=" << val << "&" ;
			pp += 2 ;
			// the cURL lib allocated the escaped versions of the
			// param strings; we must free them here
			curl_free( key ) ;
			curl_free( val ) ;
	}
	postBuf << std::flush ;
}



