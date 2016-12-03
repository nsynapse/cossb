
#include "example_cat_db_log.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(example_cat_db_log)

example_cat_db_log::example_cat_db_log()
:cossb::interface::icomponent(COMPONENT(example_cat_db_log)) {

}

example_cat_db_log::~example_cat_db_log() {

}

bool example_cat_db_log::setup()
{
	return true;
}

bool example_cat_db_log::run()
{
	if(!_task)
		create_task(example_cat_db_log::write);
	return true;
}

bool example_cat_db_log::stop()
{

	return true;
}

void example_cat_db_log::request(cossb::base::message* const msg)
{
	switch(msg->get_frame()->type)
	{
		case cossb::base::msg_type::REQUEST:
		{
			cossb_log->log(log::loglevel::INFO, fmt::format("Request for DB : {}", msg->raw()));
		} break;
		case cossb::base::msg_type::DATA: break;
		case cossb::base::msg_type::SIGNAL: break;
		default:
			cossb_log->log(log::loglevel::INFO, "Received message has unsupported type.");
	}
}

void example_cat_db_log::write()
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
