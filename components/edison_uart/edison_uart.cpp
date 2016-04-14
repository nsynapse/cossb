/*
 * edison_uart.cpp
 *
 *  Created on: 2016. 2. 26.
 *      Author: hwang
 */

#include "edison_uart.hpp"
#include <cossb.hpp>
#include <string>
#include <mraa.hpp>

using namespace std;

USE_COMPONENT_INTERFACE(edison_uart)

edison_uart::edison_uart()
:cossb::interface::icomponent(COMPONENT(edison_uart)){
	// TODO Auto-generated constructor stub

}

edison_uart::~edison_uart() {
	if(_uart)
		delete _uart;
}

bool edison_uart::setup()
{
	string port = "/dev/ttyACM0";
	for(auto value: get_profile()->get(profile::section::property, "port"))
		port = value.asString("/dev/ttyACM0");

	int baudrate = 115200;
	for(auto value: get_profile()->get(profile::section::property, "baudrate"))
		baudrate = value.asInt(115200);

	try {
		_uart = new mraa::Uart("/dev/ttyACM0");
		if(_uart->setBaudRate(baudrate) != mraa::SUCCESS)
			cossb_log->log(log::loglevel::ERROR, "Error setting parity on UART");
		if(_uart->setMode(8, mraa::UART_PARITY_NONE, 1) != mraa::SUCCESS)
			cossb_log->log(log::loglevel::ERROR, "Error setting parity on UART");
		if (_uart->setFlowcontrol(false, false) != mraa::SUCCESS)
			cossb_log->log(log::loglevel::ERROR, "Error setting flow control UART");
	} catch (std::exception& e) {
		cossb_log->log(log::loglevel::ERROR, fmt::format("{}", e.what()));
		return false;
	    }

	return true;
}

bool edison_uart::run()
{
	return true;
}

bool edison_uart::stop()
{
	return true;
}

void edison_uart::request(cossb::base::message* const msg)
{
	switch(msg->get_frame()->type)
	{
		case cossb::base::msg_type::REQUEST:
		{
			if(!msg->get_frame()->topic.compare("service/uart/write")) {
				cossb_log->log(log::loglevel::INFO, fmt::format("write data : {}", msg->show().c_str()));
				_uart->writeStr(msg->show());
			}
		}
			break;
		case cossb::base::msg_type::DATA: break;
		case cossb::base::msg_type::SIGNAL: break;
		default:
			cossb_log->log(log::loglevel::INFO, "Received message has unsupported type.");
		}
}
