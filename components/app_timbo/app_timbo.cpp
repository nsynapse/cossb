
#include "app_timbo.hpp"
#include <cossb.hpp>
#include <string>

using namespace std;

USE_COMPONENT_INTERFACE(app_timbo)

app_timbo::app_timbo()
:cossb::interface::icomponent(COMPONENT(app_timbo)){

}

app_timbo::~app_timbo() {

}

bool app_timbo::setup()
{
	return true;
}

bool app_timbo::run()
{
	cossb::message msg(this, cossb::base::msg_type::REQUEST);
	msg.pack(0x02);
	cossb_broker->publish("app_timbo_command", msg);
	cossb_log->log(log::loglevel::INFO, "App Timbo : Request RECORD");

	return true;
}

bool app_timbo::stop()
{
	return true;
}

void app_timbo::subscribe(cossb::message* const msg)
{

	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST: break;
	case cossb::base::msg_type::DATA: {

	} break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::EVENT: break;
	}
}



