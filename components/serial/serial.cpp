
#include "serial.hpp"
#include <cossb.hpp>
#include <string>

using namespace std;

USE_COMPONENT_INTERFACE(serial)

serial::serial()
:cossb::interface::icomponent(COMPONENT(serial)){
	// TODO Auto-generated constructor stub

}

serial::~serial() {
	if(_serial)
		delete _serial;
}

bool serial::setup()
{
	_port = get_profile()->get(profile::section::property, "port").asString("/dev/ttyS0");
	unsigned int baudrate = get_profile()->get(profile::section::property, "baudrate").asInt(115200);

	if(!_serial)
		_serial = new libserial;

	if(!_serial->open(_port.c_str(), baudrate)) {
		if(_serial) {
			delete _serial;
			_serial = nullptr;
		}
		cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot open {}({})",_port, baudrate));
		return false;
	}

	cossb_log->log(log::loglevel::INFO, fmt::format("Open {}({})",_port, baudrate));

	return true;
}

bool serial::run()
{
	if(!_read_task)
		_read_task = create_task(serial::read);

	return true;
}

bool serial::stop()
{
	destroy_task(_read_task);

	return true;
}

void serial::subscribe(cossb::message* const msg)
{
	if(!_serial->is_opened()){
		cossb_log->log(log::loglevel::ERROR, fmt::format("{} is not opened", _port));
		return;
	}

	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST: break;
	case cossb::base::msg_type::DATA: {
		try
		{
			vector<unsigned char> data = boost::any_cast<vector<unsigned char>>(*msg->get_data());
			_serial->write((const char*)data.data(), data.size());
			cossb_log->log(log::loglevel::INFO, fmt::format("Write {} byte(s) to the serial", data.size()));
		}
		catch(const boost::bad_any_cast&){
			cossb_log->log(log::loglevel::ERROR, "Invalid type casting");
		}
	} break;
	case cossb::base::msg_type::RESPONSE: break;
	}
}

void serial::read()
{
	while(1) {
		try {
			if(_serial) {
				const unsigned int len = 1024;
				unsigned char* buffer = new unsigned char[len];
				int readsize = _serial->read(buffer, sizeof(unsigned char)*len);

				if(readsize>0) {
					cossb_log->log(log::loglevel::INFO, fmt::format("Received {} Byte(s) from {}",readsize, _port));
					cossb::message _msg(this, base::msg_type::DATA);
					vector<unsigned char> data(buffer, buffer+readsize);
					_msg.pack(data);
					cossb_broker->publish("serial_read", _msg);
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
