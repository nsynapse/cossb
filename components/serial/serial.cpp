
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
	cossb_log->log(log::loglevel::INFO, "Receive Message");

	if(!_serial)
		return;

	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::DATA: { cossb_log->log(log::loglevel::INFO, fmt::format("Received : {}", msg->show()));} break;
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
					cossb_log->log(log::loglevel::INFO, fmt::format("read {} Byte(s)",readsize));
				}

				delete []buffer;
				boost::this_thread::sleep(boost::posix_time::milliseconds(0));
			}
		}
		catch(thread_interrupted&) {
			break;
		}
	}
}
