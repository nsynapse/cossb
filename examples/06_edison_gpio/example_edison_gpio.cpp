
#include "example_edison_gpio.hpp"

#include <cossb.hpp>

USE_COMPONENT_INTERFACE(example_edison_gpio)

example_edison_gpio::example_edison_gpio()
:cossb::interface::icomponent(COMPONENT(example_edison_gpio))
{

}

example_edison_gpio::~example_edison_gpio()
{

}

bool example_edison_gpio::setup()
{
	return true;
}

bool example_edison_gpio::run()
{
	return true;
}

bool example_edison_gpio::stop()
{
	return true;
}

void example_edison_gpio::request(cossb::base::message* const msg)
{
	switch(msg->get_frame()->type)
	{
		case cossb::base::msg_type::DATA:
			if(!msg->get_frame()->topic.compare("service/print"))
				printout(msg->show().c_str());
		break;

		case cossb::base::msg_type::REQUEST: break;
		case cossb::base::msg_type::RESPONSE: break;
	}
}

void example_edison_gpio::printout(const char* msg)
{
	cossb_log->log(cossb::log::loglevel::INFO, fmt::format("[Message Received] : {}", msg));
}


