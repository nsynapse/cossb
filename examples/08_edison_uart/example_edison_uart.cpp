
#include "example_edison_uart.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(example_edison_uart)

example_edison_uart::example_edison_uart()
:cossb::interface::icomponent(COMPONENT(example_edison_uart))
{

}

example_edison_uart::~example_edison_uart()
{

}

bool example_edison_uart::setup()
{
	if(!_task)
			create_task(example_edison_uart::write);

	return true;
}

bool example_edison_uart::run()
{
	return true;
}

bool example_edison_uart::stop()
{
	destroy_task(_task);

	return true;
}

void example_edison_uart::request(cossb::base::message* const msg)
{

}

void example_edison_uart::write()
{
	try
	{
		while(1) {
		cossb::base::message msg(this, base::msg_type::REQUEST);

		msg["data"] = { 0x01, 0x02, 0x0f };
		cossb_broker->publish("example_uart_write", msg);
		cossb_log->log(cossb::log::loglevel::INFO, fmt::format("UART Message : {}",msg.show()));

		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		}
	}
	catch(thread_interrupted&) {
		break;
	}
}

