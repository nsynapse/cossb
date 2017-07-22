/*
 * message.cpp
 *
 *  Created on: 2015. 10. 12.
 *      Author: hwang
 */

#include "message.hpp"
#include <interface/icomponent.hpp>
#include <util/uuid.hpp>

namespace cossb {
namespace base {

message::message(interface::icomponent* component, msg_type type)
{
	frame.type = type;
	frame.from = component->get_name();
}

message::message(const char* component_name, msg_type type)
{
	frame.type = type;
	frame.from = component_name;
}

void message::parse(string sdata){
	data = json::parse(sdata.c_str());
	//type
	if(data.find("type")!=data.end()){
		if(data["type"].is_string()) {
			string t = data["type"];
			if(!t.compare("request")) frame.type = msg_type::REQUEST;
			else if(!t.compare("data")) frame.type = msg_type::DATA;
			else if(!t.compare("response")) frame.type = msg_type::RESPONSE;
			else if(!t.compare("signal")) frame.type = msg_type::SIGNAL;
		}
	}
}

bool message::is_empty(){
	return frame.encoded_data.empty();
}

bool message::exist(const char* key) const {
	return (data.find(key)!=data.end());
}

} /* namespace base */
} /* namespace cossb */
