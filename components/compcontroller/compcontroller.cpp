/*
 * compcontroller.cpp
 *
 *  Created on: 2016. 8. 15.
 *      Author: hwang
 */

#include "compcontroller.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(compcontroller)

compcontroller::compcontroller()
:cossb::interface::icomponent(COMPONENT(compcontroller)){
	// TODO Auto-generated constructor stub

}

compcontroller::~compcontroller() {
	// TODO Auto-generated destructor stub
}

bool compcontroller::setup()
{

	return true;
}

bool compcontroller::run()
{


	return true;
}

bool compcontroller::stop()
{


	return true;
}

void compcontroller::request(cossb::base::message* const msg)
{
	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST: {
		//run topic subscribe
		/*if(!msg->get_frame()->topic.compare("control/component/run")) {
			if(msg->get_frame()->type==base::msg_type::REQUEST){
				if(!(*msg)["component"].is_null() && (*msg)["component"].is_string()){
					string component = (*msg)["component"];
					cossb_component_manager->run(component.c_str());
				}
			}
		}*/

		//stop topic subscribe
		/*if(!msg->get_frame()->topic.compare("control/component/stop")) {
			if(msg->get_frame()->type==base::msg_type::REQUEST){
				if(!(*msg)["component"].is_null() && (*msg)["component"].is_string()){
					string component = (*msg)["component"];
					cossb_component_manager->run(component.c_str());
				}
			}
		}*/

		//do topic topic subscribe
		if(!msg->get_frame()->topic.compare("control/component/do")) {
			if((*msg)["component"].is_string() && (*msg)["command"].is_string()){
				string component = (*msg)["component"];
				string command = (*msg)["command"];
				if(!command.compare("run"))
					cossb_component_manager->run(component.c_str());
				else if(!command.compare("stop"))
					cossb_component_manager->stop(component.c_str());
			}
		}

	} break;
	case cossb::base::msg_type::DATA: break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::SIGNAL: break;
	}
}
