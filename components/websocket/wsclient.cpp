/*
 * wsclient.cpp
 *
 *  Created on: 2016. 4. 20.
 *      Author: hwang
 */

#include "wsclient.hpp"
#include <cossb.hpp>
#include <algorithm>

USE_COMPONENT_INTERFACE(wsclient)

void handle_message(const std::string & message)
{

	cossb::base::message msg("wsclient", base::msg_type::REQUEST);
	msg.parse(message);
	cout << msg.show() << endl;
	//cossb_broker->publish("websocket_read",msg);

	cossb_log->log(log::loglevel::INFO, fmt::format("***Websocket Message Received : {}",message.c_str()));


}

wsclient::wsclient()
:cossb::interface::icomponent(COMPONENT(wsclient)){
	// TODO Auto-generated constructor stub

}

wsclient::~wsclient() {

	if(_client){
		_client->close();
		delete _client;
	}
}

bool wsclient::setup()
{
	_uri = get_profile()->get(profile::section::property, "uri").asString("ws://localhost:9002");
	_client = easywsclient::WebSocket::from_url(_uri.c_str());
	if(_client) {
		if(_client->getReadyState()!=easywsclient::WebSocket::CLOSED){
			cossb_log->log(log::loglevel::INFO, fmt::format("Connected to the {} websocket server",_uri));
		}
		else {
			cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot connect to the {} websocket server",_uri));
			_client->close();
		}
	}
	else {
		cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot connect to the {} websocket server",_uri));
	}

	return true;
}

bool wsclient::run()
{
	if(!_socket_task)
		_socket_task = create_task(wsclient::read);

	return true;
}

bool wsclient::stop()
{
	destroy_task(_socket_task);

	return true;
}

void wsclient::request(cossb::base::message* const msg)
{
	switch(msg->get_frame()->type){
		case cossb::base::msg_type::REQUEST: {
			cossb_log->log(log::loglevel::INFO, msg->show());

			if(_client){
				if(_client->getReadyState()!=easywsclient::WebSocket::CLOSED){
					std::lock_guard<std::mutex> lock(_lock);
					_client->send(msg->show());
					_client->poll(0);
				}
				else{
					cossb_log->log(log::loglevel::INFO, fmt::format("Try reconnect to the websocker server {}",_uri));
					_client->close();
					this->setup();
				}
			}
			else {
				cossb_log->log(log::loglevel::ERROR, fmt::format("Try reconnect to the websocker server {}",_uri));
				this->setup();
			}

		} break;
		case cossb::base::msg_type::DATA: break;
		case cossb::base::msg_type::RESPONSE: break;
		case cossb::base::msg_type::SIGNAL: break;

	}
}

void wsclient::read()
{
	while(1) {
		try {
			if(_client){
				if(_client->getReadyState()!=easywsclient::WebSocket::CLOSED){
					std::lock_guard<std::mutex> lock(_lock);
					_client->dispatch(handle_message);
				}
			}

			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
		}
		catch(thread_interrupted&) {
			break;
		}
	}
}
