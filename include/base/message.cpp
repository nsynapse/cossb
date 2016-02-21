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

	cossb::util::uuid random_topic;
	frame.pub_topic = component->get_profile()->get(profile::section::info, "publish").asString(random_topic.str());
}

} /* namespace base */
} /* namespace cossb */
