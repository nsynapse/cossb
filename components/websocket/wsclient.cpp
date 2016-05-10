/*
 * wsclient.cpp
 *
 *  Created on: 2016. 4. 20.
 *      Author: hwang
 */

#include "wsclient.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(wsclient)

void handle_message(const std::string & message)
{
	cossb_log->log(log::loglevel::INFO, fmt::format("Websocket Message : {}",message.c_str()));

}

wsclient::wsclient()
:cossb::interface::icomponent(COMPONENT(wsclient)){
	// TODO Auto-generated constructor stub

}

wsclient::~wsclient() {
	delete _client;
}

bool wsclient::setup()
{

	string url = get_profile()->get(profile::section::property, "url").asString("ws://localhost:9090");
	cossb_log->log(log::loglevel::INFO, fmt::format("Web Socket URL : {}",url));

	_client = easywsclient::WebSocket::from_url(url);

	return true;
}

bool wsclient::run()
{
	/*if(!_socket_task)
		_socket_task = create_task(wsclient::socket_control);*/

	return true;
}

bool wsclient::stop()
{
	//destroy_task(_socket_task);

	return true;
}

void wsclient::request(cossb::base::message* const msg)
{
	if(_client->getReadyState()==easywsclient::WebSocket::CLOSED) {
		cossb_log->log(log::loglevel::ERROR, "Websocket connection was closed.");
		return;
	}

	switch(msg->get_frame()->type)
	{
		case cossb::base::msg_type::REQUEST:
		{
			if(!msg->get_frame()->topic.compare("service/websocket/write")) {
				if((*msg)["data"].is_array()) {
					std::vector<unsigned char> raw = (*msg)["data"];
					cossb_log->log(log::loglevel::INFO, fmt::format("Websocket write {} byte(s): {}", raw.size(), msg->show()));
					//_client->send("test message");
				}
			}
		}
			break;
		case cossb::base::msg_type::DATA: break;
		case cossb::base::msg_type::SIGNAL: break;
		default:
			cossb_log->log(log::loglevel::INFO, "Received message has unsupported type.");
	}
}

void wsclient::socket_control()
{

}
