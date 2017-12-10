

#include "wsclient.hpp"
#include <cossb.hpp>
#include <algorithm>

USE_COMPONENT_INTERFACE(wsclient)

void handle_message(const std::string & message)
{
	cossb_log->log(log::loglevel::INFO, fmt::format("Message : {}", message));

}

wsclient::wsclient()
:cossb::interface::icomponent(COMPONENT(wsclient)){
	// TODO Auto-generated constructor stub

}

wsclient::~wsclient() {

}

bool wsclient::setup()
{
	for(auto uri:get_profile()->gets(profile::section::property, "endpoint")){
		string u = uri.asString("ws://localhost::9002");

		_client = easywsclient::WebSocket::from_url(u.c_str());
		if(_client->getReadyState()==easywsclient::WebSocket::OPEN){
			cossb_log->log(log::loglevel::INFO, fmt::format("Connected to the {} websocket server",u));
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
	_client->close();
	delete _client;

	destroy_task(_socket_task);

	return true;
}

void wsclient::subscribe(cossb::message* const msg)
{
	switch(msg->get_frame()->type){
		case cossb::base::msg_type::REQUEST:{

			string pack = boost::any_cast<string>(*msg->get_data());
			/*easywsclient::WebSocket::pointer endpoint = _client_map.find(uri)->second;
			if(endpoint->getReadyState()!=easywsclient::WebSocket::CLOSED){
				endpoint->send(pack);
			}*/

		} break;
		case cossb::base::msg_type::DATA: break;
		case cossb::base::msg_type::RESPONSE: break;
		case cossb::base::msg_type::EVENT: break;

	}
}

void wsclient::read()
{
	while(1) {
		try {
			if(_client->getReadyState()!=easywsclient::WebSocket::CLOSED){
				_client->poll();
				_client->dispatch(handle_message);
			}

			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
		}
		catch(thread_interrupted&) {
			break;
		}
	}
}
