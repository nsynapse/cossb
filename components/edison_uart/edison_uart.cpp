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
#include <base/message.hpp>

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
	string port = get_profile()->get(profile::section::property, "port").asString("/dev/ttyACM0");
	int baudrate = get_profile()->get(profile::section::property, "baudrate").asInt(115200);

	cossb_log->log(log::loglevel::INFO, fmt::format("UART Profile Info : {}, {}", port, baudrate));


	try {
		_uart = new mraa::Uart(0);
	} catch (std::exception& e) {
		cossb_log->log(log::loglevel::ERROR, fmt::format("{}, likely invalid platform config", e.what()));
	}

	try {
		_uart = new mraa::Uart(port);

		if(_uart->setBaudRate(baudrate) != mraa::SUCCESS)
			cossb_log->log(log::loglevel::ERROR, "Error setting parity on UART");

		if(_uart->setMode(8, mraa::UART_PARITY_NONE, 1) != mraa::SUCCESS)
			cossb_log->log(log::loglevel::ERROR, "Error setting parity on UART");

		if (_uart->setFlowcontrol(false, false) != mraa::SUCCESS)
			cossb_log->log(log::loglevel::ERROR, "Error setting flow control UART");

	} catch (std::exception& e) {
		cossb_log->log(log::loglevel::ERROR, fmt::format("{}, Error while setting up raw UART, do you have a uart?", e.what()));
		return false;
	    }

	return true;
}

bool edison_uart::run()
{
	if(!_read_task)
		_read_task = create_task(edison_uart::read);

	return true;
}

bool edison_uart::stop()
{
	destroy_task(_read_task);

	return true;
}

void edison_uart::request(cossb::base::message* const msg)
{
	switch(msg->get_frame()->type)
	{
		case cossb::base::msg_type::REQUEST:
		{
			if(!msg->get_frame()->topic.compare("service/uart/write")) {
				if((*msg)["data"].is_array()) {
					std::vector<unsigned char> raw = (*msg)["data"];
					cossb_log->log(log::loglevel::INFO, fmt::format("UART write {} byte(s): {}", raw.size(), msg->show()));
					_uart->write((const char*)raw.data(), raw.size());
				}
			}
		}
			break;
		case cossb::base::msg_type::DATA: break;
		case cossb::base::msg_type::SIGNAL: break;
		default:
			cossb_log->log(log::loglevel::INFO, "Received message has unsupported type.");
		}
}

void edison_uart::read()
{
	while(1) {
		try {
			if(_uart) {
				const unsigned int len = 1024;
				unsigned char* buffer = new unsigned char[len];
				int readsize = _uart->read((char*)buffer, len);

				if(readsize>0) {
					cossb_log->log(log::loglevel::INFO, fmt::format("UART read {} Byte(s)",readsize));

					//publish message with received data
					cossb::base::message msg(this, base::msg_type::REQUEST);
					for(int i=0;i<readsize;i++)
						msg["data"].push_back(buffer[i]);
					cossb_broker->publish("edison_uart_read", msg);

				}

				delete []buffer;
				boost::this_thread::sleep(boost::posix_time::milliseconds(100));	//time limit for async read
			}
		}
		catch(thread_interrupted&) {
				break;
			}
	}
}

