/*
 * rpi_spi.cpp
 *
 *  Created on: 2016. 2. 26.
 *      Author: hwang
 */

#include "rpi_spi.hpp"
#include <cossb.hpp>
#include <string>
#include <3rdparty/bcm2835.h>
#include <tuple>

using namespace std;

#define PIN RPI_BPLUS_GPIO_J8_05

using namespace std;

USE_COMPONENT_INTERFACE(rpi_spi)

rpi_spi::rpi_spi()
:cossb::interface::icomponent(COMPONENT(rpi_spi)){
	// TODO Auto-generated constructor stub

}

rpi_spi::~rpi_spi() {

}

bool rpi_spi::setup()
{
	if(!bcm2835_init())
		return false;

	if(!bcm2835_spi_begin())
		return false;

	//set gpio as input
	//bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
	//bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_UP);

	//set default spi
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

	return true;
}

bool rpi_spi::run()
{

	//1. check gpio
	//unsigned char value = bcm2835_gpio_lev(PIN);
	bcm2835_gpio_write(PIN, HIGH);

	//cossb_log->log(log::loglevel::INFO, fmt::format("GPIO : {}", value));

	/*if(value!=0x00){
		//cossb_log->log(log::loglevel::INFO, "GPIO : HIGH");
		unsigned char readata = bcm2835_spi_transfer(_write_byte);
		cossb_log->log(log::loglevel::INFO, fmt::format("Read SPI : {}", readata));
	}
	else {
		//cossb_log->log(log::loglevel::INFO, "GPIO : LOW");
	}*/

	return true;
}

bool rpi_spi::stop()
{
	//1. close spi
	bcm2835_spi_end();

	if(!bcm2835_close())
		return false;

	return true;
}

void rpi_spi::request(cossb::message* const msg)
{
	switch(msg->get_frame()->type) {
		case cossb::base::msg_type::REQUEST: break;
		case cossb::base::msg_type::DATA: {

			//subscribe emotion data
			try {
			unsigned char emotion_data = boost::any_cast<unsigned char>(*msg);
			_write_byte = emotion_data;	//copy

			cossb_log->log(log::loglevel::INFO, fmt::format("SPI write : {}", emotion_data));
			}
			catch(const boost::bad_any_cast&){
				cossb_log->log(log::loglevel::ERROR, "Invalid type casting..");
			}
		} break;
		case cossb::base::msg_type::RESPONSE: break;
		case cossb::base::msg_type::EVENT:  break;
		}
}

void rpi_spi::read()
{

}

