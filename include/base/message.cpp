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

} /* namespace base */
} /* namespace cossb */
