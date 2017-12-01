
#include "nanopi.hpp"
#include <cossb.hpp>
#include <wiringPi.h>

using namespace std;

USE_COMPONENT_INTERFACE(nanopi)

nanopi::nanopi()
:cossb::interface::icomponent(COMPONENT(nanopi)){
	// TODO Auto-generated constructor stub

}

nanopi::~nanopi() {

}

bool nanopi::setup()
{
	wiringPiSetup () ;

	//set output port
	for(auto outport:get_profile()->gets(profile::section::property, "output")){
		int port = outport.asInt(-1);
		if(port>0){
			_gpio_out_port.push_back(port);
			pinMode (port, OUTPUT);
		}
	}

	//set input port
	for(auto inport:get_profile()->gets(profile::section::property, "input")){
		int port = inport.asInt(-1);
		if(port>0){
			_gpio_in_port.push_back(port);
			pinMode (port, IN);
		}
	}

	//create task for gpio read
	_gpio_task = create_task(nanopi::read);

	return true;
}

bool nanopi::run()
{
	return true;
}

bool nanopi::stop()
{

	return true;
}

void nanopi::subscribe(cossb::message* const msg)
{
	switch(msg->get_frame()->type) {
		case cossb::base::msg_type::REQUEST: break;
		case cossb::base::msg_type::DATA: {

			//subscribe emotion data
			try {
				map<int, unsigned char> data = boost::any_cast<map<int, unsigned char>>(*msg->get_data()); //{key, value} pair

				//1. extract keys
				vector<int> keys;
				for(auto& port: data)
					keys.push_back(port.first);

				//2. compare port set, then write data if it is outport
				for(auto& key:keys){
					cossb_log->log(log::loglevel::INFO, fmt::format("GPIO write key : {}", key));
					if(_portmap.find(key)!=_portmap.end()){
						if(_portmap[key]){ //output port
							if(data[key]==0x00)
								digitalWrite(key, LOW);
							else
								digitalWrite(key, HIGH);
						}
					}
				}
			}
			catch(const boost::bad_any_cast&){
				cossb_log->log(log::loglevel::ERROR, "Invalid type casting, should be map<int, unsigned char> type.");
			}
		} break;
		case cossb::base::msg_type::RESPONSE: break;
		case cossb::base::msg_type::EVENT:  break;
		}
}

void nanopi::read()
{
	while(1) {
		try {

			digitalRead()
			if(_uart) {
				const unsigned int len = 1024;
				unsigned char* buffer = new unsigned char[len];
				int readsize = _uart->read(buffer, sizeof(unsigned char)*len);

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

