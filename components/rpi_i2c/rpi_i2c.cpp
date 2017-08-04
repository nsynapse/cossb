

#include "rpi_i2c.hpp"
#include <cossb.hpp>
#include <string>
#include <3rdparty/bcm2835.h>
#include <tuple>

using namespace std;


USE_COMPONENT_INTERFACE(rpi_i2c)

rpi_i2c::rpi_i2c()
:cossb::interface::icomponent(COMPONENT(rpi_i2c)){
	// TODO Auto-generated constructor stub

}

rpi_i2c::~rpi_i2c() {

}

bool rpi_i2c::setup()
{
	int address = get_profile()->get(profile::section::property, "address").asInt(1);
	address = (int)(address/10)*16+(int)(address/10);

	if(!bcm2835_init())
		return false;

	cossb_log->log(log::loglevel::INFO, fmt::format("Set I2C Address : 0x{0:x}", address));

	return true;
}

bool rpi_i2c::run()
{

	return true;
}

bool rpi_i2c::stop()
{

	if(!bcm2835_close())
		return false;

	return true;
}

void rpi_i2c::subscribe(cossb::message* const msg)
{
	switch(msg->get_frame()->type) {
		case cossb::base::msg_type::REQUEST: break;
		case cossb::base::msg_type::DATA: {

			//subscribe emotion data
			try {
//			unsigned char emotion_data = boost::any_cast<unsigned char>(*msg);
//			_write_byte = emotion_data;	//copy

			//cossb_log->log(log::loglevel::INFO, fmt::format("request SPI write : {}", emotion_data));
			}
			catch(const boost::bad_any_cast&){
				cossb_log->log(log::loglevel::ERROR, "Invalid type casting..");
			}
		} break;
		case cossb::base::msg_type::RESPONSE: break;
		case cossb::base::msg_type::EVENT:  break;
		}
}

void rpi_i2c::read()
{

}

