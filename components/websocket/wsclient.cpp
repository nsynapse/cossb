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
	cossb_log->log(log::loglevel::INFO, fmt::format("Websocket Message Received : {}",message.c_str()));

}

wsclient::wsclient()
:cossb::interface::icomponent(COMPONENT(wsclient)){
	// TODO Auto-generated constructor stub

}

wsclient::~wsclient() {
	for(auto client:_client_map){
		client.second->close();
		delete client.second;
	}
	_client_map.clear();
}

bool wsclient::setup()
{
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
	switch(msg->get_frame()->type)
	{
		case cossb::base::msg_type::REQUEST:
		{
			if(!msg->get_frame()->topic.compare("service/websocket/write")) {
				//check  uri
				if((*msg)["uri"].empty()){
					cossb_log->log(log::loglevel::ERROR, "Message does not have URI");
					return;
				}

				//add url and
				if(!(*msg)["uri"].is_null() && (*msg)["uri"].is_string()) {
					string uri = (*msg)["uri"];
					if(_client_map.find(uri)==_client_map.end()){
						_client_map[uri] = easywsclient::WebSocket::from_url(uri);
						cossb_log->log(log::loglevel::INFO, fmt::format("Add new Websocket URL {}", uri));
					}

					if(!(*msg)["data"].empty()){
						cossb_log->log(log::loglevel::INFO, fmt::format("Send to websocket server : {}", msg->show()));

						if(_client_map[uri]->getReadyState()!=easywsclient::WebSocket::CLOSED){
							_client_map[uri]->send(msg->show());
							_client_map[uri]->poll(0);
						}
						else
							cossb_log->log(log::loglevel::WARN, "Cannot send message : No data");
					}
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

void wsclient::read()
{
	/*while(1) {
		try {
			if(_client)
				_client->dispatch(handle_message);
				boost::this_thread::sleep(boost::posix_time::milliseconds(100));
		}
		catch(thread_interrupted&) {
			break;
		}
	}*/
}
