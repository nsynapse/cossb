

#include "wsclient.hpp"
#include <cossb.hpp>
#include <algorithm>
#include <ext/json.hpp>
#include <base/log.hpp>
#include <base/broker.hpp>
#include <boost/any.hpp>
#include <string>

USE_COMPONENT_INTERFACE(wsclient)

void on_receive(const std::string & message)
{
	nlohmann::json _json_data = nlohmann::json::parse(message);

	if(_json_data.find("service")!=_json_data.end()){
		string wsdata = _json_data.dump();
		string service = _json_data["service"];
		cossb::message msg("wsclient", base::msg_type::REQUEST);
		msg.pack(wsdata);
		cossb_log->log(log::loglevel::INFO, fmt::format("> Publish websocket message : {}", wsdata));
		cossb_broker->publish(service.c_str(), msg);
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
			if(!_socket_read_task)
				_socket_read_task = create_task(wsclient::_ws_read);
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
	destroy_task(_socket_read_task);

	if(_client){
		_client->close();
		delete _client;
		_client = nullptr;
	}
	return true;
}

void wsclient::subscribe(cossb::message* const msg)
{
	switch(msg->get_frame()->type){
		case cossb::base::msg_type::REQUEST:{
			try {
				string pack = boost::any_cast<string>(*msg->get_data());
				_client->send(pack); //pack string must be json format
			} catch(boost::bad_any_cast&){ }
		} break;
		case cossb::base::msg_type::DATA: break;
		case cossb::base::msg_type::RESPONSE: break;
		case cossb::base::msg_type::EVENT: break;

	}
}

void wsclient::_ws_read()
{
	while(1) {
		try {
			if(_client->getReadyState()!=easywsclient::WebSocket::CLOSED){
				_client->poll();
				_client->dispatch(on_receive);
			}
			if(boost::this_thread::interruption_requested()) break;
			boost::this_thread::sleep(boost::posix_time::milliseconds(100));

		}
		catch(thread_interrupted&) {
			_client->close();
			break;
		}
	}
}
