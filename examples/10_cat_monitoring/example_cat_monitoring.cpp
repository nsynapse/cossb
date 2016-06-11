
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
	static unsigned long try_count = 1;
	static char id = 0x01;
	while(1) {
		try {
			cossb::base::message msg(this, base::msg_type::REQUEST);

			//test protocol for monitoring test
			//it will be converted as [ 0xff | 0xff | id | length | error | value | checksum ]
			msg["data"] = {0xff, 0xff, 0x01, 0x03, 0x00, 0x20, 0xdb };
			cossb_broker->publish("example_cat_push", msg);

			cossb_log->log(cossb::log::loglevel::INFO, fmt::format("[{}] Send Test Message : {}",try_count++, msg.show()));
			boost::this_thread::sleep(boost::posix_time::milliseconds(500));

			id++;
			if(id>0x05){
				id=0x01;
			}

		} catch(thread_interrupted&) {
			break;
		}
	}
}
