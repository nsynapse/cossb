#include "app_timbo.hpp"
#include <cossb.hpp>
#include <string>
#include <algorithm>
#include <ext/json.hpp>
#include <base/log.hpp>
#include <base/broker.hpp>
#include <fstream>
#include <vector>
#include <base/task.hpp>
#include <file/collector.hpp>

using namespace std;

#define HEAD		0x55
#define END		0xaa
#define SET		0xf0
#define TRAJ		0x0d
#define RECORD	0x02
#define PLAY		0x03
#define STOP		0x04
#define PING		0x24
#define TRAJECTORY_DUMP	0x37
#define TRAJECTORY_PLAY	0x2e

void app_timbo::key_id_setting(int value){
	unsigned char frame[] = {HEAD, 0x07, SET, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, END};
	memcpy(frame+3, _group_id, sizeof(_group_id));
	cossb::message _msg(this, base::msg_type::DATA);
	vector<unsigned char> data(frame, frame+sizeof(frame));
	cossb_broker->publish("app_timbo_command", _msg);

}

void app_timbo::key_id_select(int value){

}

void app_timbo::key_send_trajectory(int value){
	unsigned char frame[] = {HEAD, 0x07, 0x0f, TRAJ, 0x00, 0x00, 0x00, END};
	cossb::message _msg(this, base::msg_type::DATA);
	vector<unsigned char> data(frame, frame+sizeof(frame));
	cossb_broker->publish("timbo_write", _msg);
}

void app_timbo::timbo_record(){
	unsigned char frame[] = {HEAD, 0x03, 0x0f, RECORD, 0x00, END};
	cossb::message _msg(this, base::msg_type::DATA);
	vector<unsigned char> data(frame, frame+sizeof(frame));
	_msg.pack(data);
	cossb_log->log(log::loglevel::INFO, "> Publish 'RECORD' command");
	cossb_broker->publish("timbo_write", _msg);
}

void app_timbo::timbo_play(){
	unsigned char frame[] = {HEAD, 0x03, 0x0f, PLAY, 0x00, END};
	cossb::message _msg(this, base::msg_type::DATA);
	vector<unsigned char> data(frame, frame+sizeof(frame));
	_msg.pack(data);
	cossb_log->log(log::loglevel::INFO, "> Publish 'PLAY' command");
	cossb_broker->publish("timbo_write", _msg);
}


void app_timbo::timbo_stop(){
	unsigned char frame[] = {HEAD, 0x03, 0x0f, STOP, 0x00, END};
	cossb::message _msg(this, base::msg_type::DATA);
	vector<unsigned char> data(frame, frame+sizeof(frame));
	_msg.pack(data);
	cossb_log->log(log::loglevel::INFO, "> Publish 'STOP' command");
	cossb_broker->publish("timbo_write", _msg);
}

void app_timbo::timbo_ping(){
	unsigned char frame[] = {HEAD, 0x03, 0x0f, PING, 0x00, END};
	cossb::message _msg(this, base::msg_type::DATA);
	vector<unsigned char> data(frame, frame+sizeof(frame));
	_msg.pack(data);
	cossb_log->log(log::loglevel::INFO, "> Publish 'PING' command");
	cossb_broker->publish("timbo_write", _msg);
}

void app_timbo::timbo_trajectory_play(int page){

	map<int, vector<unsigned char>> trj_map; //[id, trajectory]
	file::collector* trj_files = new file::collector("./contents/", ".trj");

	//1. load trajectory data
	for(auto& file : trj_files->getList()){
		size_t pos = file.filename.find(fmt::format("page{}_", page));
		if(pos!=string::npos){
			string str_id = file.filename.substr(pos+6);
			int id = ::stoi(str_id.c_str());
			cossb_log->log(log::loglevel::INFO, fmt::format("[Device ID : {}] Found Trajectory file : {}", id, file.relative));

			ifstream f;
			f.open(file.absolute, ios::in|ios::binary);
			if(f.is_open()){
				f.seekg(0, ios::end);	//set the pointer to the end of file
				int size = f.tellg();
				f.seekg(0, ios::beg);
				unsigned char* data = new unsigned char[size];
				f.read((char*)data, size);
				vector<unsigned char> trjtmp;
				trjtmp.insert(trjtmp.end(), &data[0], &data[size]);
				trj_map[id] = trjtmp;	//insert to map
				delete []data;
				cossb_log->log(log::loglevel::INFO, fmt::format("Loaded Trajectory file : {} ({}) ",file.filename, trjtmp.size()));
			}
			else
				cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot be loaded Trajectory file : {}",file.relative));
			f.close();
		}
	}
	delete trj_files;

	//2. multiple trajectory download..
	for(auto& trj:trj_map){
		unsigned char start[] = {HEAD, 0x06, (unsigned char)trj.first, 0x0c, 0x0, 0x55, 0x7f, 0x01, END}; //start
		vector<unsigned char> sdata(start, start+sizeof(start)/sizeof(start[0]));
		cossb::message smsg(this, base::msg_type::DATA);
		smsg.pack(sdata);
		cossb_broker->publish("timbo_write", smsg);
		boost::this_thread::sleep(boost::posix_time::milliseconds(100/trj_map.size()));
	}
	cossb_log->log(log::loglevel::INFO, "Now Trajectories downloading..");

	//data downloading...
	const int offset = 20;
	int pos = 0;

	while(1){
		int done = 0;
		cossb_log->log(log::loglevel::INFO, fmt::format("pos : {}", pos));
		for(auto& trj:trj_map){
			if(pos<(int)trj.second.size()){
				unsigned char trj_pack[] = {HEAD, 0x05, (unsigned char)trj.first, TRAJ, trj.second[pos+2], trj.second[pos+3], 0x00, END};
				cossb::message vmsg(this, base::msg_type::DATA);
				vector<unsigned char> data2(trj_pack, trj_pack+sizeof(trj_pack));
				vmsg.pack(data2);
				cossb_log->log(log::loglevel::INFO, fmt::format("[Device ID : {}] Send Trajectory : {}, {}", trj.first, trj.second[pos+2], trj.second[pos+3]));
				cossb_broker->publish("timbo_write", vmsg);
				boost::this_thread::sleep(boost::posix_time::milliseconds(100/trj_map.size()));
			}
			else
				done++;
		}

		pos+=offset;

		boost::this_thread::sleep(boost::posix_time::milliseconds(100/trj_map.size()));
		if(done>=(int)trj_map.size())
			break;
	}

	//end
	for(auto& trj:trj_map){
		cossb::message tmsg(this, base::msg_type::DATA);
		unsigned char tail[] = {HEAD, 0x03, (unsigned char)trj.first, 0x04, 0x00, END};
		vector<unsigned char> data3(tail, tail+sizeof(tail));
		tmsg.pack(data3);
		cossb_broker->publish("timbo_write", tmsg);
	}

	cossb_log->log(log::loglevel::INFO, "Trajectory Downloading...Done.");
}

void app_timbo::timbo_trajectory_dump(int page) {
	unsigned char frame[] = {HEAD, 0x03, TRAJECTORY_DUMP, 0x00, END};
	vector<unsigned char> packet(frame, frame+sizeof(frame)/sizeof(frame[0]));
	std::tuple<int, vector<unsigned char>> data = std::make_tuple(page, packet);
	cossb::message _msg(this, base::msg_type::REQUEST);
	_msg.pack(data);
	cossb_log->log(log::loglevel::INFO, "> Publish 'TRAJECTORY DUMP' command");
	cossb_broker->publish("timbo_write", _msg);
}

void app_timbo::ebook_sound_play()
{
	cossb::message msg(this, cossb::base::msg_type::REQUEST);
	nlohmann::json _json_msg;
	_json_msg["command"] = "sound_play";
	msg.pack(_json_msg.dump());
	cossb_broker->publish("websocket_write_msg",msg);
	cossb_log->log(log::loglevel::INFO, "Sound Play on Ebook");
}
