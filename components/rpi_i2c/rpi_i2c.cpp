

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
	cossb_log->log(log::loglevel::INFO, fmt::format("Set I2C Address : 0x{0:x}", address));

	if(!bcm2835_init())
		return false;

	if(!bcm2835_i2c_begin()){
		cossb_log->log(log::loglevel::ERROR, "I2C Begin");
		return false;
	}

	bcm2835_i2c_setSlaveAddress((unsigned char)address);
	bcm2835_i2c_setClockDivider(_clk_div);

	cossb_log->log(log::loglevel::INFO, fmt::format("Slave Address set to : 0x{0:x}", address));
	cossb_log->log(log::loglevel::INFO, fmt::format("I2C Clock Divider set to : {}", _clk_div));

	return true;
}

bool rpi_i2c::run()
{

	return true;
}

bool rpi_i2c::stop()
{
	bcm2835_i2c_end();

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
			char emotion_data = boost::any_cast<char>(*msg->get_data());
			bcm2835_i2c_write((const char*)emotion_data, 1);

			cossb_log->log(log::loglevel::INFO, fmt::format("Write 0x{0:x} via I2C", emotion_data));
			}
			catch(const boost::bad_any_cast&){
				cossb_log->log(log::loglevel::ERROR, "Invalid type casting");
			}
		} break;
		case cossb::base::msg_type::RESPONSE: break;
		case cossb::base::msg_type::EVENT:  break;
		}
}

void rpi_i2c::read()
{

}

