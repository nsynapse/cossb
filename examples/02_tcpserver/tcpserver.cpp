
#include "tcpserver.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(tcpserver)

tcpserver::tcpserver()
:cossb::interface::icomponent(COMPONENT(tcpserver))
{

}

tcpserver::~tcpserver()
{
	if(_server)
		delete _server;
}

bool tcpserver::setup()
{
	string port = get_profile()->get(profile::section::property, "port").asString("8000");
	if(!_server) {
		_server = new net::tcp::server(port.c_str());
	}

	return true;
}

bool tcpserver::run()
{
	if(_server) {
		_server->start();
	}
	return true;
}

bool tcpserver::stop()
{
	if(_server) {
		_server->stop();
	}
	return true;
}

void tcpserver::request(cossb::base::message* const msg)
{

}
