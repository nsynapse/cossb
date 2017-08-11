
#include "rpi_gpio.hpp"
#include <cossb.hpp>
#include <3rdparty/bcm2835.h>

using namespace std;

USE_COMPONENT_INTERFACE(rpi_gpio)

rpi_gpio::rpi_gpio()
:cossb::interface::icomponent(COMPONENT(rpi_gpio)){
	// TODO Auto-generated constructor stub

}

rpi_gpio::~rpi_gpio() {

}

bool rpi_gpio::setup()
{
	if(!bcm2835_init())
		return false;

	vector<int> outports = get_profile()->gets(profile::section::property, "output");
	vector<int> inports = get_profile()->gets(profile::section::property, "input");

	for(auto const& port:outports){
		_portmap[port] = 1;
		bcm2835_gpio_fsel(port, BCM2835_GPIO_FSEL_OUTP);
	}

	for(auto const& port:inports){
		_portmap[port] = 0;
		bcm2835_gpio_fsel(port, BCM2835_GPIO_FSEL_INPT);
		bcm2835_gpio_set_pud(port, BCM2835_GPIO_PUD_UP);
	}


	return true;
}

bool rpi_gpio::run()
{
	map<int, unsigned char> port_read;
	string read="";
	for(auto const& port:_portmap){
		if(!port.second){
			port_read[port.first] = bcm2835_gpio_lev(port.first);
			read += fmt::format("{}:0x{0:x}\t",port.first, port_read[port.first]);
		}
	}

	if(!port_read.empty()){
		cossb::message msg(this, cossb::base::msg_type::DATA);
		msg.pack(port_read);
		cossb_broker->publish("rpi_gpio_read", msg);
		cossb_log->log(log::loglevel::INFO, fmt::format("Read GPIO: {}",read));
	}


	return true;
}

bool rpi_gpio::stop()
{
	if(!bcm2835_close())
		return false;

	return true;
}

void rpi_gpio::subscribe(cossb::message* const msg)
{
	switch(msg->get_frame()->type) {
		case cossb::base::msg_type::REQUEST: break;
		case cossb::base::msg_type::DATA: {

			//subscribe emotion data
			try {
				map<int, unsigned char> data = boost::any_cast<map<int, unsigned char>>(*msg); //{key, value} pair

				//1. extract keys
				vector<int> keys;
				for(auto const& port: data)
					keys.push_back(port.first);

				//2. compare port set, then write data if it is outport
				for(auto const& key:keys){
					if(_portmap.find(key)!=_portmap.end()){
						if(_portmap[key]){ //output port
							bcm2835_gpio_write(key, data[key]); //write data
							cossb_log->log(log::loglevel::INFO, fmt::format("Write GPIO({}) : 0x{0:x}", key, data[key]));
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


