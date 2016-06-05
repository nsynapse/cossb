
#include "example_cat_monitoring.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(example_cat_monitoring)

example_cat_monitoring::example_cat_monitoring()
:cossb::interface::icomponent(COMPONENT(example_cat_monitoring))
{
	// TODO Auto-generated constructor stub

}

example_cat_monitoring::~example_cat_monitoring() {
	// TODO Auto-generated destructor stub
}


bool example_cat_monitoring::setup()
{

	if(!_task)
		create_task(example_cat_monitoring::write);

	return true;
}

bool example_cat_monitoring::run()
{
	return true;
}

bool example_cat_monitoring::stop()
{
	destroy_task(_task);

	return true;
}

void example_cat_monitoring::request(cossb::base::message* const msg)
{

}

void example_cat_monitoring::write()
{
	static char id = 0x01;
	while(1) {
		try {
			cossb::base::message msg(this, base::msg_type::REQUEST);

			//test protocol for monitoring test
			//it will be converted as [ 0xff | 0xff | id | length | error | value | checksum ]
			msg["data"]["id"] = id;
			msg["data"]["error"] = 0x00;
			msg["data"]["value"] = {0x55};
			cossb_broker->publish("example_cat_write", msg);

			//cossb_log->log(cossb::log::loglevel::INFO, fmt::format("Write Message : {}",msg.show()));
			boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

			id++;
			if(id>0x05){
				id=0x01;
			}

		} catch(thread_interrupted&) {
			break;
		}
	}
}
