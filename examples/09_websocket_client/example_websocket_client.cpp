
#include "example_websocket_client.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(example_websocket_client)

example_websocket_client::example_websocket_client()
:cossb::interface::icomponent(COMPONENT(example_websocket_client))
{
	// TODO Auto-generated constructor stub

}

example_websocket_client::~example_websocket_client() {
	// TODO Auto-generated destructor stub
}


bool example_websocket_client::setup()
{
	return true;
}

bool example_websocket_client::run()
{
	return true;
}

bool example_websocket_client::stop()
{
	return true;
}

void example_websocket_client::request(cossb::base::message* const msg)
{

}
