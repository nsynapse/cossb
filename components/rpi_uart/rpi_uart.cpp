/*
 * rpi_uart.cpp
 *
 *  Created on: 2016. 2. 26.
 *      Author: hwang
 */

#include "rpi_uart.hpp"
#include <cossb.hpp>
#include <string>

using namespace std;

USE_COMPONENT_INTERFACE(rpi_uart)

rpi_uart::rpi_uart()
:cossb::interface::icomponent(COMPONENT(rpi_uart)){
	// TODO Auto-generated constructor stub

}

rpi_uart::~rpi_uart() {
	if(_uart)
		delete _uart;
}

bool rpi_uart::setup()
{
	_port = get_profile()->get(profile::section::property, "port").asString("/dev/ttyS0");
	unsigned int baudrate = get_profile()->get(profile::section::property, "baudrate").asInt(115200);

	if(!_uart)
		_uart = new libserial;

	if(!_uart->open(_port.c_str(), baudrate)) {
		if(_uart) {
			delete _uart;
			_uart = nullptr;
		}
		cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot open {}({})",_port, baudrate));
		return false;
	}

	cossb_log->log(log::loglevel::INFO, fmt::format("Open {}({})",_port, baudrate));

	return true;
}

bool rpi_uart::run()
{
	if(!_read_task)
		_read_task = create_task(rpi_uart::read);

	return true;
}

bool rpi_uart::stop()
{
	destroy_task(_read_task);

	return true;
}

void rpi_uart::subscribe(cossb::message* const msg)
{
	if(!_uart->is_opened()){
		cossb_log->log(log::loglevel::ERROR, fmt::format("{} is not opened", _port));
		return;
	}

	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST: break;
	case cossb::base::msg_type::DATA: {
		try {
			vector<unsigned char> data = boost::any_cast<vector<unsigned char>>(*msg->get_data());
			_uart->write((const char*)data.data(), data.size());
			cossb_log->log(log::loglevel::INFO, fmt::format("Write {} byte(s) to the serial", data.size()));

		}
		catch(const boost::bad_any_cast&){
			cossb_log->log(log::loglevel::ERROR, "Invalid type casting");
		}
	}break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::EVENT:  break;
	}
}

void rpi_uart::read()
{
	while(1) {
		try {
			if(_uart) {
					const unsigned int len = 2048;
					unsigned char* buffer = new unsigned char[len];

					int readsize = _uart->read(buffer, len);
					if(readsize>0) {
						cossb_log->log(log::loglevel::INFO, fmt::format("Read {} Byte(s) from serial",readsize));

						cossb::message _msg(this, base::msg_type::DATA);
						vector<unsigned char> data(buffer, buffer+readsize);
						_msg.set(data);
						cossb_broker->publish("rpi_uart_read", _msg);
						cossb_log->log(log::loglevel::INFO, "Publish data received from UART");
					}

					delete []buffer;
					boost::this_thread::sleep(boost::posix_time::milliseconds(10));
			}
		}
		catch(thread_interrupted&) {
			break;
		}
	}
}

