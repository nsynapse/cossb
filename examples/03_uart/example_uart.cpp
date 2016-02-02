
#include "example_uart.hpp"

#include <cossb.hpp>

USE_COMPONENT_INTERFACE(example_uart)

example_uart::example_uart()
:cossb::interface::icomponent(COMPONENT(example_uart)){
	// TODO Auto-generated constructor stub

}

example_uart::~example_uart() {

}

bool example_uart::setup()
{


	return true;
}

bool example_uart::run()
{


	return true;
}

bool example_uart::stop()
{


	return true;
}

void example_uart::request(cossb::base::message* const msg)
{

}

