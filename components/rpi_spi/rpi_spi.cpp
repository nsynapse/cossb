/*
 * rpi_spi.cpp
 *
 *  Created on: 2016. 2. 26.
 *      Author: hwang
 */

#include "rpi_spi.hpp"
#include <cossb.hpp>
#include <string>
#include "bcm2835.h"

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

	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

	return true;
}

bool rpi_spi::run()
{
	while(1) {

	}
	unsigned char send_data = 0x23;
	unsigned char read_data = bcm2835_spi_transfer(send_data);

	return true;
}

bool rpi_spi::stop()
{
	bcm2835_spi_end();

	if(!bcm2835_close())
		return false;

	return true;
}

void rpi_spi::request(cossb::message* const msg)
{

}

void rpi_spi::read()
{

}

