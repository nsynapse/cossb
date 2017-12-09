

#include "wsclient.hpp"
#include <cossb.hpp>
#include <algorithm>

USE_COMPONENT_INTERFACE(wsclient)

void handle_message(const std::string & message)
{
	cossb_log->log(log::loglevel::INFO, "message");

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

		_client_map[u] = easywsclient::WebSocket::from_url(u.c_str());

		if(_client_map[u]){
			if(_client_map[u]->getReadyState()==easywsclient::WebSocket::OPEN){
				cossb_log->log(log::loglevel::INFO, fmt::format("Connected to the {} websocket server",u));
				_reconnect[u] = false;
			}
		}
		else {
			cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot connect to the server {}.",u));
			_reconnect[u] = true;
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
	for(auto it=_client_map.begin(); it!=_client_map.end(); ++it){
		if(it->second) {
			it->second->close();
			delete it->second;
		}
	}
	_client_map.clear();

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
			for(auto it=_client_map.begin(); it!=_client_map.end(); ++it) {
				if(it->second){
					if(it->second->getReadyState()!=easywsclient::WebSocket::CLOSED){
						std::lock_guard<std::mutex> lock(_lock);
						it->second->poll();
						it->second->dispatch(handle_message);

						if(!_reconnect[it->first]){
							cossb_log->log(log::loglevel::INFO, fmt::format("Connected to the {} websocket server",it->first));
							_reconnect[it->first] = true;
						}
					}
					else {
						cossb_log->log(log::loglevel::INFO, fmt::format("Disconnected. Trying to reconnect {}",it->first));
						it->second = easywsclient::WebSocket::from_url(it->first.c_str());
						_reconnect[it->first] = false;
					}

				}
				//try to reconnect
				else {
						//cossb_log->log(log::loglevel::INFO, fmt::format("Disconnected. Try to reconnect {}",it->first));
					//
					it->second = easywsclient::WebSocket::from_url(it->first.c_str());
					_reconnect[it->first] = false;
					//
				}
			}

			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
		}
		catch(thread_interrupted&) {
			break;
		}
	}
}
