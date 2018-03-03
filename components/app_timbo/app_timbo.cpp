
#include "app_timbo.hpp"
#include <cossb.hpp>
#include <string>
#include <algorithm>
#include <ext/json.hpp>
#include <base/log.hpp>
#include <base/broker.hpp>
#include <base/task.hpp>
#include <net/util.hpp>

using namespace std;

USE_COMPONENT_INTERFACE(app_timbo)

app_timbo::app_timbo()
:cossb::interface::icomponent(COMPONENT(app_timbo)){
	memset(_group_id, 0x00, sizeof(_group_id));
}

app_timbo::~app_timbo() {

}

bool app_timbo::setup()
{
	string _if = get_profile()->get(profile::section::property, "if").asString("eth0");
	net::macAddress _mac = net::getMacAddress(_if.c_str());
	memcpy(_group_id, _mac.address, sizeof(_group_id));

	cossb_log->log(log::loglevel::INFO, fmt::format("Group ID(MAC Address) : {}:{}:{}:{}:{}",
			_mac.address[0],_mac.address[1],_mac.address[2],_mac.address[3],_mac.address[4]));

	return true;
}

bool app_timbo::run()
{
	return true;
}

bool app_timbo::stop()
{

	return true;
}

void app_timbo::subscribe(cossb::message* const msg)
{

	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST:
	{
		//commands from Web GUI
		try {
			string data = boost::any_cast<string>(*msg->get_data());
			nlohmann::json _json_data = nlohmann::json::parse(data);

			if(_json_data.find("command")!=_json_data.end())
			{
				string command = _json_data["command"].get<std::string>();

				//play trajectory
				if(!command.compare("trajectory_play")){
					int page = _json_data["page"].get<int>();
					this->timbo_trajectory_play(page);
				}
				//dump trajectory
				else if(!command.compare("trajectory_dump")){
					int page = _json_data["page"].get<int>();
					this->timbo_trajectory_dump(page);
				}
				else if(!command.compare("record")){this->timbo_record();} //record command
				else if(!command.compare("play")){this->timbo_play();}	//play command
				else if(!command.compare("stop")){this->timbo_stop();}	//stop command
				else if(!command.compare("ping")){this->timbo_ping();}	//ping command
			}
			else
				cossb_log->log(log::loglevel::INFO, "No Command");
		}catch(const boost::bad_any_cast&){
			cossb_log->log(log::loglevel::ERROR, "[app_timbo] Invalid casting for REQUEST");
		}
	}
		break;

	case cossb::base::msg_type::DATA: {
		try
		{
			//key press
			map<int, int> data = boost::any_cast<map<int, int>>(*msg->get_data());

			//map to key functions
			for(auto& key:data){
				if(key.first==12) key_id_setting(key.second);
				if(key.first==13) key_send_trajectory(key.second);
				if(key.first==11) key_id_select(key.second);
			}
		}
		catch(const boost::bad_any_cast&){
			cossb_log->log(log::loglevel::ERROR, "[app_timbo] Invalid casting for DATA");
		}

	} break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::EVENT: break;
	}
}








