
#include "example_uart.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(example_uart)

example_uart::example_uart()
:cossb::interface::icomponent(COMPONENT(example_uart)){
	// TODO Auto-generated constructor stub

}

example_uart::~example_uart() {

}

bool example_uart::setup()
{

	return true;
}

bool example_uart::run()
{

	if(!_write_task)
		create_task(example_uart::do_write);

	return true;
}

bool example_uart::stop()
{
	destroy_task(_write_task);

	return true;
}

void example_uart::request(cossb::base::message* const msg)
{

}

void example_uart::do_write()
{
	while(1){

		try {

		cossb::base::message _msg(this);
		_msg["data"] = "this is test message";

		cossb_broker->publish(_msg);
		cossb_log->log(cossb::log::loglevel::INFO, "publish");
		boost::this_thread::sleep(boost::posix_time::milliseconds(500));

		}
		catch(cossb::broker::exception& e) {
			cossb_log->log(cossb::log::loglevel::ERROR, fmt::format("{}", e.what()).c_str());
		}
	}
}

