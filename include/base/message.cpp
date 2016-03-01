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

} /* namespace base */
} /* namespace cossb */
