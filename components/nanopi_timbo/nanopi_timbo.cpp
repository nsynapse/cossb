
#include "nanopi.hpp"
#include <cossb.hpp>
#include <wiringPi.h>
#include <algorithm>

#define LED1	21
#define LED2	22
#define LED3	23
#define LED4	24
#define BTN1	11	//ID Selection
#define BTN2	12	//ID Setting
#define BTN3	13	//Trajectory
#define SW1		15	//Guidebook page1
#define SW2		16	//Guidebook page2
#define SW3		18	//Guidebook page3
#define SW4		19	//Guidebook page4

const unsigned int gpio_out[] = {LED1, LED2, LED3, LED3 };
const unsigned int gpio_in[] = {BTN1, BTN2, BTN3 };
const unsigned int gpio_sw[] = {SW1, SW2, SW3, SW4};

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
	wiringPiSetup ();

	for(int i=0;i<sizeof(gpio_out);i++)
		pinMode(gpio_out[i], OUTPUT);

	for(int i=0;i<sizeof(gpio_in);i++)
		pinMode(gpio_in[i], INPUT);

	for(int i=0;i<sizeof(gpio_sw);i++)
		pinMode(gpio_sw[i], INPUT);


	//create task for gpio read
	//_gpio_task = create_task(nanopi::read);

	return true;
}

bool nanopi::run()
{
	return true;
}

bool nanopi::stop()
{
	//destroy_task(_gpio_task);
	return true;
}

void nanopi::subscribe(cossb::message* const msg)
{
	switch(msg->get_frame()->type) {
		case cossb::base::msg_type::REQUEST: break;
		case cossb::base::msg_type::DATA: {

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

void nanopi::read()
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

