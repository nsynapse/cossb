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

using namespace std;

#define HEAD	0x55
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

	//print
	for(int i=0;i<(int)sizeof(frame);i++)
		cout << (int)frame[i];
	cout << endl;

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
	cossb_broker->publish("timbo_write", _msg);
	cossb_log->log(log::loglevel::INFO, fmt::format("Record : Publish to Nanopi : {} bytes", data.size()));
}

void app_timbo::timbo_play(){
	unsigned char frame[] = {HEAD, 0x03, 0x0f, PLAY, 0x00, END};
	cossb::message _msg(this, base::msg_type::DATA);
	vector<unsigned char> data(frame, frame+sizeof(frame));
	_msg.pack(data);
	cossb_broker->publish("timbo_write", _msg);
	cossb_log->log(log::loglevel::INFO, fmt::format("Play : Publish to Nanopi : {} bytes", data.size()));
}


void app_timbo::timbo_stop(){
	unsigned char frame[] = {HEAD, 0x03, 0x0f, STOP, 0x00, END};
	cossb::message _msg(this, base::msg_type::DATA);
	vector<unsigned char> data(frame, frame+sizeof(frame));
	_msg.pack(data);
	cossb_broker->publish("timbo_write", _msg);
	cossb_log->log(log::loglevel::INFO, fmt::format("Stop : Publish to Nanopi : {} bytes", data.size()));
}

void app_timbo::timbo_ping(){
	unsigned char frame[] = {HEAD, 0x03, 0x0f, PING, 0x00, END};
	cossb::message _msg(this, base::msg_type::DATA);
	vector<unsigned char> data(frame, frame+sizeof(frame));
	_msg.pack(data);
	cossb_broker->publish("timbo_write", _msg);
	cossb_log->log(log::loglevel::INFO, fmt::format("Ping : Publish to Nanopi : {} bytes", data.size()));
}

void app_timbo::timbo_trajectory_play(int page, int module){

	//1. read trajectory file
	ifstream file;
	vector<unsigned char> trajectory;
	file.open(fmt::format("./contents/page{}_{}.trj", page, module), ios::in|ios::binary);
	//read trajectory file
	if(file.is_open()){
		file.seekg(0, ios::end);	//set the pointer to the end of file
		int size = file.tellg();
		file.seekg(0, ios::beg);
		unsigned char* data = new unsigned char[size];
		file.read((char*)data, size);
		trajectory.insert(trajectory.end(), &data[0], &data[size]);
		delete []data;
		cossb_log->log(log::loglevel::INFO, fmt::format("Loaded Trajectory file : page{}_{}.trj ({}bytes) ",page, module, trajectory.size()));
	}
	file.close();

	cossb_log->log(log::loglevel::INFO, "Trajectory Playing...");

	unsigned char start[] = {HEAD, 0x03, 0x0f, 0xc, 0x00, END}; //record start
	vector<unsigned char> sdata(start, start+sizeof(start)/sizeof(start[0]));
	cossb::message smsg(this, base::msg_type::DATA);
	smsg.pack(sdata);
	cossb_broker->publish("timbo_write", smsg);

	//2. send start
	unsigned char header[] = {HEAD, 0x03, 0x0f, 0x2e, 0x00, END}; //record start
	vector<unsigned char> data1(header, header+sizeof(header)/sizeof(header[0]));
	cossb::message hmsg(this, base::msg_type::DATA);
	hmsg.pack(data1);
	cossb_broker->publish("timbo_write", hmsg);

	//3. send trajectory
	const int offset = 5;
	for(int i=0;i<trajectory.size();i+=offset){
		unsigned char trj[] = {HEAD, 0x04, 0x0f, TRAJ, trajectory[i+2], trajectory[i+3], END};
		cossb::message vmsg(this, base::msg_type::DATA);
		vector<unsigned char> data2(trj, trj+sizeof(trj));
		vmsg.pack(data2);
		cossb_broker->publish("timbo_write", vmsg);
		cossb_log->log(log::loglevel::INFO, fmt::format("Send Trajectory : {}, {}", trajectory[i+2], trajectory[i+3]));
		boost::this_thread::sleep(boost::posix_time::milliseconds(20));
	}

	//4. end
	cossb::message tmsg(this, base::msg_type::DATA);
	unsigned char tail[] = {HEAD, 0x03, 0x0f, 0x04, 0x00, END};
	vector<unsigned char> data3(tail, tail+sizeof(tail));
	tmsg.pack(data3);
	cossb_broker->publish("timbo_write", tmsg);
	cossb_log->log(log::loglevel::INFO, "Trajectory Playing...Done.");

}

void app_timbo::timbo_trajectory_dump(int page, int module) {
	unsigned char frame[] = {HEAD, 0x03, TRAJECTORY_DUMP, 0x00, END};
	vector<unsigned char> packet(frame, frame+sizeof(frame)/sizeof(frame[0]));
	std::tuple<int, int, vector<unsigned char>> data = std::make_tuple(page, module, packet);

	cossb::message _msg(this, base::msg_type::REQUEST);
	_msg.pack(data);
	cossb_broker->publish("timbo_write", _msg);
	cossb_log->log(log::loglevel::INFO, fmt::format("Trajectory Dump : Publish to Nanopi : {} bytes", packet.size()));
}
