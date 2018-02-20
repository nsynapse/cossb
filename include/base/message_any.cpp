
#include "message_any.hpp"
#include <interface/icomponent.hpp>

namespace cossb {

message::message()
:cossb::interface::imessage<boost::any>("", base::msg_type::DATA)
{

}

message::message(const char* component_name, base::msg_type type = base::msg_type::DATA)
:cossb::interface::imessage<boost::any>(component_name, type) {
	this->msg_frame.type = type;
	this->msg_frame.from = component_name;
}

message::message(interface::icomponent* component, base::msg_type type = base::msg_type::DATA)
:cossb::interface::imessage<boost::any>(component, type) {
	this->msg_frame.type = type;
	this->msg_frame.from = component->get_name();
}

message::~message(){

}
void message::pack(boost::any data){
	this->msg_frame.data = data;
}

void message::set(boost::any data){
		this->msg_frame.data = data;
}

}
