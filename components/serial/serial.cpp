
#include "serial.hpp"
#include <cossb.hpp>

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
	string port = get_profile()->get(profile::section::property, "port").asString("/dev/ttyS0");
	unsigned int baudrate = get_profile()->get(profile::section::property, "baudrate").asInt(115200);

	if(!_serial)
		_serial = new libserial;

	if(!_serial->open(port.c_str(), baudrate)) {
		if(_serial) {
			delete _serial;
			_serial = nullptr;
		}
		cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot open {}({})",port, baudrate));
		return false;
	}

	cossb_log->log(log::loglevel::INFO, fmt::format("Open {}({})",port, baudrate));

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

void serial::request(cossb::base::message* const msg)
{
	if(!_serial)
		return;

	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST: {
		//write
		if(!(*msg)["data"].is_null()){
			if((*msg)["data"].is_array()){
				std::vector<unsigned char> raw = (*msg)["data"];
				_serial->write((const char*)raw.data(), raw.size());
				cossb_log->log(log::loglevel::INFO, fmt::format("Write {} byte(s) to the serial : {}", raw.size(), (*msg)["data"].dump()));
			}
		}
	} break;
	case cossb::base::msg_type::DATA: break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::SIGNAL: break;
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
					cossb_log->log(log::loglevel::INFO, fmt::format("Read {} Byte(s) from serial",readsize));
					//publish message with received data
					cossb::base::message msg(this, base::msg_type::REQUEST);

					for(int i=0;i<readsize;i++)
						msg["data"].push_back(buffer[i]);

					cossb_broker->publish("serial_read", msg);
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
