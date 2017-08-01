
#include "helloworld.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(helloworld)

helloworld::helloworld()
:cossb::interface::icomponent(COMPONENT(helloworld))
{

}

helloworld::~helloworld()
{

}

bool helloworld::setup()
{
	cossb_log->log(cossb::log::loglevel::INFO, "called helloworld component setup");
	return true;
}
bool helloworld::run()
{
	cossb_log->log(cossb::log::loglevel::INFO, "called helloworld component run");

	cossb::message msg(this, base::msg_type::DATA);
	msg.set(1);
	cossb_broker->publish("capture", msg);


	return true;
}
bool helloworld::stop()
{
	cossb_log->log(cossb::log::loglevel::INFO, "called helloworld component stop");
	return true;
}

void helloworld::request(cossb::message* const msg)
{
	cossb_log->log(cossb::log::loglevel::INFO, "called helloworld component request");
}
