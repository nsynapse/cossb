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
}

bool message::is_empty(){
	return frame.encoded_data.empty();
}

} /* namespace base */
} /* namespace cossb */
