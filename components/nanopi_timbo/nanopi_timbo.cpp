
#include "nanopi_timbo.hpp"
#include <cossb.hpp>
#include <wiringPi.h>
#include <algorithm>
#include <base/log.hpp>
#include <base/broker.hpp>
#include <tuple>

using namespace std;

//wiring pi index
#define LED1		13
#define LED2		6
#define LED3		14
#define LED4		10
#define BTN1		0	//ID Selection
#define BTN2		1	//ID Setting
#define BTN3		2	//Trajectory
#define SW1		3	//Guidebook page1
#define SW2		4	//Guidebook page2
#define SW3		5	//Guidebook page3
#define SW4		12	//Guidebook page4

const unsigned int gpio_out[] = {LED1, LED2, LED3, LED3 };
const unsigned int gpio_in[] = {BTN1, BTN2, BTN3 };
const unsigned int gpio_sw[] = {SW1, SW2, SW3, SW4};

using namespace std;

USE_COMPONENT_INTERFACE(nanopi_timbo)

nanopi_timbo::nanopi_timbo()
:cossb::interface::icomponent(COMPONENT(nanopi_timbo)){
	// TODO Auto-generated constructor stub


}

nanopi_timbo::~nanopi_timbo() {
	if(_uart)
		delete _uart;
}

bool nanopi_timbo::setup()
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

	wiringPiSetup ();

	for(int i=0;i<(int)sizeof(gpio_out);i++)
		pinMode(gpio_out[i], OUTPUT);

	for(int i=0;i<(int)sizeof(gpio_in);i++)
		pinMode(gpio_in[i], INPUT);

	for(int i=0;i<(int)sizeof(gpio_sw);i++)
		pinMode(gpio_sw[i], INPUT);


	//perform tasks
	_uart_task = create_task(nanopi_timbo::uart_read);
	_gpio_task = create_task(nanopi_timbo::gpio_read);

	return true;
}

bool nanopi_timbo::run()
{
	return true;
}

bool nanopi_timbo::stop()
{
	destroy_task(_gpio_task);
	destroy_task(_uart_task);
	return true;
}

void nanopi_timbo::subscribe(cossb::message* const msg)
{
	switch(msg->get_frame()->type) {
		case cossb::base::msg_type::REQUEST: {

			try {
				typedef std::tuple<int, int, vector<unsigned char>> req;
				req data = boost::any_cast<req>(*msg->get_data());

				int page, module;
				vector<unsigned char> packet;
				std::tie(page, module, packet) = data;

				cossb_log->log(log::loglevel::INFO, fmt::format("page : {}, module : {}, size : {}", page, module, packet.size()));

			} catch(const boost::bad_any_cast&){
				//cossb_log->log(log::loglevel::ERROR, "Invalid type casting");
			}
		}break;
		case cossb::base::msg_type::DATA: {
			//uart data
			try
			{
				vector<unsigned char> data = boost::any_cast<vector<unsigned char>>(*msg->get_data());
				_uart->write((const char*)data.data(), data.size());
				cossb_log->log(log::loglevel::INFO, fmt::format("Write {} byte(s) to the serial", data.size()));
			}
			catch(const boost::bad_any_cast&){
				//cossb_log->log(log::loglevel::ERROR, "Invalid type casting");
			}

			//subscribe gpio write
			try {
				/*map<int, unsigned char> data = boost::any_cast<map<int, unsigned char>>(*msg->get_data()); //{key, value} pair

				//1. extract keys
				vector<int> keys;
				for(auto& port: data)
					keys.push_back(port.first);

				//2. compare port set, then write data if it is outport
				for(auto& key:keys){
					cossb_log->log(log::loglevel::INFO, fmt::format("GPIO write key : {}", key));
					if(_gpio_port_map.find(key)!=_gpio_port_map.end()){
						if(_gpio_port_map[key]){ //output port
							if(data[key]==0x00)
								digitalWrite(key, LOW);
							else
								digitalWrite(key, HIGH);
						}
					}
				}*/
			}
			catch(const boost::bad_any_cast&){
				cossb_log->log(log::loglevel::ERROR, "Invalid type casting, should be map<int, unsigned char> type.");
			}
		} break;
		case cossb::base::msg_type::RESPONSE: break;
		case cossb::base::msg_type::EVENT:  break;
		}
}
void nanopi_timbo::uart_read(){
	while(1) {
		try {
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

					//debug
					for(auto& c:data)
						cout << (int)c << " ";
					cout << endl;
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

void nanopi_timbo::gpio_read()
{
	/*vector<int> input_port;
	for(auto& port:_gpio_port_map)
		if(!port.second)
			input_port.push_back(port.first);

	while(1) {
		try {
			map<int, int> read_gpio;
			for(auto& port:input_port)
				read_gpio[port] = digitalRead(port);

			//if changed, publish the message
			bool changed = false;
			for(auto& port:read_gpio){
				if(read_gpio[port.first]!= _gpio_port_read[port.first])
					changed = true;
			}

			if(changed){
				_gpio_port_read = read_gpio;
				cossb::message msg(this, cossb::base::msg_type::DATA);
				msg.pack(read_gpio);
				cossb_broker->publish("nanopi_gpio_read", msg);
			}

			boost::this_thread::sleep(boost::posix_time::milliseconds(300));
		}
		catch(thread_interrupted&) {
			break;
		}
	}*/
}

