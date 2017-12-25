

#include "wsclient.hpp"
#include <cossb.hpp>
#include <algorithm>
#include <ext/json.hpp>
#include <base/log.hpp>
#include <base/broker.hpp>

USE_COMPONENT_INTERFACE(wsclient)

void handle_message(const std::string & message)
{
	nlohmann::json _json_data = nlohmann::json::parse(message);

	if(_json_data.find("service")!=_json_data.end()){
		string wsdata = _json_data.dump();
		string service = _json_data["service"];
		cossb::message msg("wsclient", base::msg_type::REQUEST);
		msg.pack(wsdata);
		cossb_broker->publish(service.c_str(), msg);
		cossb_log->log(log::loglevel::INFO, fmt::format("Publish WS message : {}", wsdata));
	}

}

wsclient::wsclient()
:cossb::interface::icomponent(COMPONENT(wsclient)){
	// TODO Auto-generated constructor stub

}

wsclient::~wsclient() {

}

bool wsclient::setup()
{
	string uri = get_profile()->get(profile::section::property, "endpoint").asString("ws://localhost:9002");

	if(!_client){
		_client = easywsclient::WebSocket::from_url(uri.c_str());
		if(_client->getReadyState()==easywsclient::WebSocket::OPEN){
			cossb_log->log(log::loglevel::INFO, fmt::format("Connected to the {} websocket server",uri));
			if(!_socket_task)
				_socket_task = create_task(wsclient::read);
			return true;
		}
	}
	return false;
}

bool wsclient::run()
{

	return true;
}

bool wsclient::stop()
{
	destroy_task(_socket_task);

	_client->close();
	delete _client;

	return true;
}

void wsclient::subscribe(cossb::message* const msg)
{
	switch(msg->get_frame()->type){
		case cossb::base::msg_type::REQUEST:{

			string pack = boost::any_cast<string>(*msg->get_data());


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

			boost::this_thread::sleep(boost::posix_time::milliseconds(100));
			//if(boost::this_thread::interruption_requested()) break;
		}
		catch(thread_interrupted&) {
			_client->close();
			break;
		}
	}
}
