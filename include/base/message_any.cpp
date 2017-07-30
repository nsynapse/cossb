
#include "message_any.hpp"

namespace cossb {

message::message(const char* component_name, base::msg_type type = base::msg_type::REQUEST)
:cossb::interface::imessage<boost::any>(component_name, type) {

}

message::message(interface::icomponent* component, base::msg_type type = base::msg_type::REQUEST)
:cossb::interface::imessage<boost::any>(component, type) {

}

message::~message(){

}

void message::set(boost::any data){
		this->msg_frame.data = data;
	}

}
