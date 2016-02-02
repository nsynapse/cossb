
#include "example_tcpserver.hpp"

#include <cossb.hpp>

USE_COMPONENT_INTERFACE(example_tcpserver)

example_tcpserver::example_tcpserver()
:cossb::interface::icomponent(COMPONENT(example_tcpserver))
{

}

example_tcpserver::~example_tcpserver()
{

}

bool example_tcpserver::setup()
{
	return true;
}

bool example_tcpserver::run()
{

	return true;
}

bool example_tcpserver::stop()
{

	return true;
}

void example_tcpserver::request(cossb::base::message* const msg)
{

}
