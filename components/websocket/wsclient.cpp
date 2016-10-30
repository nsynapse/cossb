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
	cossb_broker->publish("websocket_read",msg);
	cossb_log->log(log::loglevel::INFO, fmt::format("Websocket Message Received : {}",message.c_str()));

}

wsclient::wsclient()
:cossb::interface::icomponent(COMPONENT(wsclient)){
	// TODO Auto-generated constructor stub

}

wsclient::~wsclient() {
	for(auto it=_client_map.begin(); it!=_client_map.end(); ++it){
		it->second->close();
		delete it->second;
	}
	_client_map.clear();
}

bool wsclient::setup()
{
	for(auto uri:get_profile()->gets(profile::section::property, "endpoint")){
		string u = uri.asString("ws://localhost::9002");
		_client_map[u] = easywsclient::WebSocket::from_url(u.c_str());

		if(_client_map[u]) {
			if(_client_map[u]->getReadyState()!=easywsclient::WebSocket::CLOSED){
				cossb_log->log(log::loglevel::INFO, fmt::format("Connected to the {} websocket server",u));
			}
			else {
				cossb_log->log(log::loglevel::ERROR, fmt::format("Server might not be ready {}",u));
				_client_map[u]->close();
				_client_map.erase(u);
			}
		}
		else {
			_client_map.erase(u);
			cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot connect to the {} websocket server",u));
		}
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

			if((*msg).find("uri")){
				if((*msg)["uri"].is_string()){
					string uri = (*msg)["uri"];

					//if destination uri exists
					if(_client_map.find(uri)!=_client_map.end()){
						easywsclient::WebSocket::pointer endpoint = _client_map.find(uri)->second;
						if(endpoint->getReadyState()!=easywsclient::WebSocket::CLOSED){
							endpoint->send(msg->raw());
							cossb_log->log(log::loglevel::INFO, msg->raw());
						}
						else
							cossb_log->log(log::loglevel::WARN, fmt::format("Cannot connect to the server {}.",uri));
					}
				}
			}
			else
			{
				cossb_log->log(log::loglevel::INFO, "There is no URI to send message");
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
			for(auto it=_client_map.begin(); it!=_client_map.end(); ++it) {
				if(it->second->getReadyState()!=easywsclient::WebSocket::CLOSED){
					std::lock_guard<std::mutex> lock(_lock);
					it->second->poll();
					it->second->dispatch(handle_message);
				}
			}

			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
		}
		catch(thread_interrupted&) {
			break;
		}
	}
}
