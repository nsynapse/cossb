
#include "example_filelog.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(example_filelog)

example_filelog::example_filelog()
:cossb::interface::icomponent(COMPONENT(example_filelog)) {

}

example_filelog::~example_filelog() {

}

bool example_filelog::setup()
{
	return true;
}

bool example_filelog::run()
{
	if(!_task)
		create_task(example_filelog::write);

	return true;
}

bool example_filelog::stop()
{
	destroy_task(_task);
	return true;
}

void example_filelog::request(cossb::base::message* const msg)
{

}

void example_filelog::write()
{
	int idx = 0;
	while(1) {
		try {
			cossb::base::message msg(this, base::msg_type::REQUEST);

			msg["value"] = {0xff, 0xff, 0x01, 0x03, 0x00, idx++, 0xdb };
			msg["uri"] = "ws:://192.168.0.26:9002/sensor";
			cossb_broker->publish("example_filelog_write", msg);

			cossb_log->log(cossb::log::loglevel::INFO, "Publish message");
			boost::this_thread::sleep(boost::posix_time::milliseconds(100));

		} catch(thread_interrupted&) {
			break;
		}
	}
}
