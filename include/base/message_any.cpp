
#include "message_any.hpp"

namespace cossb {

message::message(const char* component_name)
:cossb::interface::imessage<boost::any>(component_name){

}

message::message(interface::icomponent* component)
:cossb::interface::imessage<boost::any>(component){

}

message::~message(){

}

void message::set(boost::any data){
		this->msg_frame.data = data;
	}

}
