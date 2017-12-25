
#include "app_timbo.hpp"
#include <cossb.hpp>
#include <string>
#include <algorithm>
#include <ext/json.hpp>
#include <file/trj.hpp>
#include <base/log.hpp>
#include <base/broker.hpp>

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
	string gid = get_profile()->get(profile::section::property, "groupID").asString("ffffffffff");
	std::transform(gid.begin(), gid.end(), gid.begin(), ::tolower); //change lowercase
	if(gid.size()!=10){
		cossb_log->log(log::loglevel::ERROR, fmt::format("Invalid Group ID : {}", gid));
		return false;
	}

	//hex string to hex
	for(int i=0;i<5;i++){
		unsigned char l = gid.at(i);
		unsigned char h = gid.at(i+1);

		if(l>=48 && l<=57)
			_group_id[i] = 0xf0&((l-48)<<4);
		else
			_group_id[i] = 0xf0&((l-97)<<4);

		if(h>=48 && h<=57)
			_group_id[i] |= 0x0f&(h-48);
		else _group_id[i] |= 0x0f&(h-97);
	}

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
				if(!command.compare("trajectory_play")){
					int page = _json_data["page"].get<int>();
					int module = _json_data["module"].get<int>();
					this->timbo_trajectory_play(page, module);
				}	//run trajectory
				else if(!command.compare("trajectory_dump")){
					int page = _json_data["page"].get<int>();
					int module = _json_data["module"].get<int>();
					this->timbo_trajectory_dump(page, module);
				} //dump trajectory
				else if(!command.compare("record")){this->timbo_record();} //record command
				else if(!command.compare("play")){this->timbo_play();}	//play command
				else if(!command.compare("stop")){this->timbo_stop();}	//stop command
				else if(!command.compare("ping")){this->timbo_ping();}	//ping command
			}
		}catch(const boost::bad_any_cast&){}
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
		catch(const boost::bad_any_cast&){ }

	} break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::EVENT: break;
	}
}




void app_timbo::run_motion(int contents)
{
	//start
	cossb::message hmsg(this, base::msg_type::DATA);
	unsigned char header[] = {HEAD, 0x03, 0x0f, 0x2e, 0x00, END};
	vector<unsigned char> data1(header, header+sizeof(header));
	hmsg.pack(data1);
	cossb_broker->publish("timbo_write", hmsg);

	for(int i=0;i<100;i++)
	{
		//trajectory (sample)
		unsigned short value = (unsigned short)(i*10);
		unsigned char trj[] = {HEAD, 0x04, 0x0f, TRAJ, (value>>8), (value&0x00ff), END};
		cossb::message vmsg(this, base::msg_type::DATA);
		vector<unsigned char> data2(trj, trj+sizeof(trj));
		vmsg.pack(data2);
		cossb_broker->publish("timbo_write", vmsg);
		cossb_log->log(log::loglevel::INFO, fmt::format("Publish to Nanopi : {} bytes", data2.size()));
		boost::this_thread::sleep(boost::posix_time::milliseconds(20));
	}

	//end
	cossb::message tmsg(this, base::msg_type::DATA);
	unsigned char tail[] = {HEAD, 0x03, 0x0f, 0x04, 0x00, END};
	vector<unsigned char> data3(tail, tail+sizeof(tail));
	tmsg.pack(data3);
	cossb_broker->publish("timbo_write", tmsg);

}



