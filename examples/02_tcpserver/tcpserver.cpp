
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

	_server = new cossb::net::tcp::server(port.c_str());
	_server->set_response_func(response);

	return true;
}

bool tcpserver::run()
{
	if(_server) {
		cossb_log->log(log::loglevel::INFO, "run tcp server component");
		_server->start();
	}
	return true;
}

bool tcpserver::stop()
{
	if(_server) {
		_server->stop();
		cossb_log->log(log::loglevel::INFO, "stop tcp server component");
	}
	return true;
}

void tcpserver::request(cossb::base::message* const msg)
{

}

int tcpserver::response(const char* data, int len)
{
	cossb_log->log(log::loglevel::INFO, fmt::format("received {}bytes ",len));
	return len;
}

