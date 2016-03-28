
#include "example_messageprint.hpp"
#include <cossb.hpp>
#include <iostream>

USE_COMPONENT_INTERFACE(example_messageprint)

example_messageprint::example_messageprint()
:cossb::interface::icomponent(COMPONENT(example_messageprint))
{

}

example_messageprint::~example_messageprint()
{

}

bool example_messageprint::setup()
{
	return true;
}

bool example_messageprint::run()
{
	return true;
}

bool example_messageprint::stop()
{
	return true;
}

void example_messageprint::request(cossb::base::message* const msg)
{

	switch(msg->get_frame()->type)
	{
		case cossb::base::msg_type::DATA: break;
		case cossb::base::msg_type::REQUEST:
			{
				//if(msg->get_frame()->topic.compare("service/messageout"))
				cossb_log->log(cossb::log::loglevel::INFO, fmt::format("[Message Received] : {}", msg->show()));
			}
			break;
		case cossb::base::msg_type::RESPONSE: break;
		case cossb::base::msg_type::SIGNAL: break;

	}
}

void example_messageprint::printout(const char* msg)
{
	cossb_log->log(cossb::log::loglevel::INFO, fmt::format("[Message Received] : {}", msg));
}


