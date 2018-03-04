
#include "nanopi_timbo.hpp"
#include <cossb.hpp>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <algorithm>
#include <base/log.hpp>
#include <base/broker.hpp>
#include <tuple>
#include <base/task.hpp>
#include <ext/json.hpp>

using namespace std;

//wiring pi gpio index
#define LED1		8
#define LED2		9
#define LED3		7
#define LED4		1

#define BTN_ID_SEL		13	//ID Selection
#define BTN_ID_SET		14	//ID Setting
#define BTN_TRJ_PLAY	10	//Trajectory play

#define SW1		3	//Guidebook page1
#define SW2		4	//Guidebook page2
#define SW3		5	//Guidebook page3
#define SW4		12	//Guidebook page4

const unsigned int gpio_led[] = {LED1, LED2, LED3, LED4 };
const unsigned int gpio_btn[] = {BTN_ID_SEL, BTN_ID_SET, BTN_TRJ_PLAY };
const unsigned int gpio_sw[] = {SW1, SW2, SW3, SW4};

using namespace std;

USE_COMPONENT_INTERFACE(nanopi_timbo)

nanopi_timbo::nanopi_timbo()
:cossb::interface::icomponent(COMPONENT(nanopi_timbo)){
	// TODO Auto-generated constructor stub

}

nanopi_timbo::~nanopi_timbo() {

}

bool nanopi_timbo::setup()
{
	//1. read from profile
	_wl_port = get_profile()->get(profile::section::property, "wl_port").asString("/dev/ttyS0");
	unsigned int wl_baudrate = get_profile()->get(profile::section::property, "wl_baudrate").asInt(115200);

	_w_port = get_profile()->get(profile::section::property, "w_port").asString("/dev/ttyS0");
	unsigned int w_baudrate = get_profile()->get(profile::section::property, "w_baudrate").asInt(115200);

	_i2c_address = (unsigned char)get_profile()->get(profile::section::property, "i2c_address").asUInt(0);
	cossb_log->log(log::loglevel::INFO, fmt::format("I2C Address : {}",(int)_i2c_address));

	//2. create serial instances
	if(!_wl_uart)
		_wl_uart = new libserial;
	if(!_w_uart)
		_w_uart = new libserial;

	//3. serial port open (for wireless)
	if(!_wl_uart->open(_wl_port.c_str(), wl_baudrate)) {
		if(_wl_uart) {
			delete _wl_uart;
			_wl_uart = nullptr;
		}
		cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot open {}({})",_wl_port, wl_baudrate));
		return false;
	}
	cossb_log->log(log::loglevel::INFO, fmt::format("Open {}({})",_wl_port, wl_baudrate));


	//4. serial port open (for wired)
	if(!_w_uart->open(_w_port.c_str(), w_baudrate)) {
		if(_w_uart) {
			delete _w_uart;
			_w_uart = nullptr;
		}
		cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot open {}({})",_w_port, w_baudrate));
		return false;
	}
	cossb_log->log(log::loglevel::INFO, fmt::format("Open {}({})",_w_port, w_baudrate));

	//setting up wiringNP to use GPIO with default value
	wiringPiSetup ();

	//I2C configuration
	_i2c_handle = wiringPiI2CSetup(_i2c_address);
	wiringPiI2CWrite(_i2c_handle, _selected_id); //initial (all LED off)


	//gpio input initialization
	for(auto& port:gpio_btn){
		pinMode(port, INPUT);
		_prev_gpio_map[port] = digitalRead(port);
	}
	for(auto& port:gpio_sw){
		pinMode(port, INPUT);
		_prev_gpio_map[port] = digitalRead(port);
	}

	//perform tasks
	_wl_uart_read_task = create_task(nanopi_timbo::wireless_uart_read);
	_w_uart_read_task = create_task(nanopi_timbo::wired_uart_read);
	_led_task = create_task(nanopi_timbo::gpio_read);
	_ir_task = create_task(nanopi_timbo::ir_read);

	return true;
}

bool nanopi_timbo::run()
{
	return true;
}

bool nanopi_timbo::stop()
{
	destroy_task(_led_task);
	destroy_task(_ir_task);
	destroy_task(_wl_uart_read_task);
	destroy_task(_w_uart_read_task);

	if(_wl_uart){
		_wl_uart->close();
		delete _wl_uart;
		_wl_uart = nullptr;
	}

	if(_w_uart){
		_w_uart->close();
		delete _w_uart;
		_w_uart = nullptr;
	}

	return true;
}

void nanopi_timbo::subscribe(cossb::message* const msg)
{
	switch(msg->get_frame()->type) {
		case cossb::base::msg_type::REQUEST: {

			try {
				typedef std::tuple<int, vector<unsigned char>> req;
				req data = boost::any_cast<req>(*msg->get_data());

				if(_dump_file.is_open())
					_dump_file.close();

				vector<unsigned char> packet;
				std::tie(_guidebook_page, packet) = data;
				_dumping = true;
				_dump_buffer.clear();
				_dump_file.open(fmt::format("./contents/page{}_{}.trj", _guidebook_page, _selected_id), std::ofstream::in);
				_w_uart->write(packet.data(), packet.size()); //send command packet

				cossb_log->log(log::loglevel::INFO, fmt::format("Trajectory Dump Page : {}, ID : {}", _guidebook_page, _selected_id));
				cossb_log->log(log::loglevel::INFO, "Now Dumping...");

			} catch(const boost::bad_any_cast&){ }
		}break;

		case cossb::base::msg_type::DATA: {
			//uart data
			try
			{
				vector<unsigned char> data = boost::any_cast<vector<unsigned char>>(*msg->get_data());
				_wl_uart->write((const char*)data.data(), data.size());
				cossb_log->log(log::loglevel::INFO, fmt::format("Write {} byte(s) to the", data.size()));
			}
			catch(const boost::bad_any_cast&){ }
		} break;
		case cossb::base::msg_type::RESPONSE: break;
		case cossb::base::msg_type::EVENT:  break;
		}
}


void nanopi_timbo::wireless_uart_read(){
	while(1) {
		try {
			if(_wl_uart->is_opened()) {
				const unsigned int len = 1024;
				unsigned char* buffer = new unsigned char[len];
				int readsize = _wl_uart->read(buffer, sizeof(unsigned char)*len);

				if(readsize>0) {
					cossb_log->log(log::loglevel::INFO, fmt::format("Received {} Byte(s) from {}",readsize, _wl_port));

					//publish the received data
					cossb::message _msg(this, base::msg_type::DATA);
					vector<unsigned char> data(buffer, buffer+readsize);
					_msg.pack(data);
					cossb_broker->publish("nanopi_uart_read", _msg);
				}

				delete []buffer;
				if(boost::this_thread::interruption_requested())
					break;
				boost::this_thread::sleep(boost::posix_time::milliseconds(10));
			}
		}
		catch(thread_interrupted&) {
			break;
		}
	}
}

void nanopi_timbo::wired_uart_read(){
	while(1) {
		try {
			if(_w_uart->is_opened()) {
				const unsigned int len = 2048;
				unsigned char* buffer = new unsigned char[len];
				int readsize = _w_uart->read(buffer, sizeof(unsigned char)*len);

				if(readsize>0) {
					cossb_log->log(log::loglevel::INFO, fmt::format("Received {} Byte(s) from {}",readsize, _w_port));

					if(_dumping){
						//push back into the buffer
						for(int i=0;i<readsize;i++)
							_dump_buffer.push_back(buffer[i]);

						//size check
						if(_dump_buffer.size()>=5){
							if(_dump_buffer[0]==0x55 && _dump_buffer[1]==0x36){
								unsigned short len = (_dump_buffer[2] << 8 | _dump_buffer[3]);
								cossb_log->log(log::loglevel::INFO, fmt::format("Receiving trajectory.. {}%", _dump_buffer.size()/(len+1)*100));
								if(_dump_buffer.size()==(unsigned int)(len+1)*5){
									for(int i=0;i<5;i++) _dump_buffer.pop_front(); //remove header packet
									if(_dump_file.is_open()){	//save into file
										for(int i=0;i<(int)_dump_buffer.size();i++){
											_dump_file << _dump_buffer.front();
											_dump_buffer.pop_front();
										}
										_dump_file.close();
										cossb_log->log(log::loglevel::INFO, "Successfully saved.");
										_dumping = false;
									}
								}
							}
						}
					}
				}

				delete []buffer;
				if(boost::this_thread::interruption_requested())
					break;
				boost::this_thread::sleep(boost::posix_time::milliseconds(10));
			}
		}
		catch(thread_interrupted&) {
			break;
		}
	}
}

void nanopi_timbo::ir_command(const char* command, int page)
{
	cossb::message msg(this, cossb::base::msg_type::REQUEST);
	nlohmann::json _json_msg;
	_json_msg["command"] = command;
	_json_msg["page"] = page;
	msg.pack(_json_msg.dump());
	cossb_broker->publish("nanopi_websocket_read", msg);
}

void nanopi_timbo::ir_read()
{
	int prev_ir_data = 0;
	while(1){
		int ir_data = wiringPiI2CRead(_i2c_handle);

		if(prev_ir_data!=ir_data){
			switch(ir_data){
			case 1: { //record
				cossb_log->log(log::loglevel::INFO, "Record");
				ir_command("record", _guidebook_page);

			} break;
			case 2: { //play
				cossb_log->log(log::loglevel::INFO, "Play");
				ir_command("play", _guidebook_page);

			} break;
			case 3: {//stop
				cossb_log->log(log::loglevel::INFO, "Stop");
				ir_command("stop", _guidebook_page);
			} break;
			case 4: { //trajectory dump
				cossb_log->log(log::loglevel::INFO, "Trajectory Dump");
				ir_command("trajectory_dump", _guidebook_page);
			} break;
			case 5: { //trajectory play
				cossb_log->log(log::loglevel::INFO, "Trajectory Play");
				ir_command("trajectory_play", _guidebook_page);
			} break;
			}
		}

		prev_ir_data = ir_data;

		if(boost::this_thread::interruption_requested()) break;
		boost::this_thread::sleep(boost::posix_time::milliseconds(100)); //read period = 500ms
	}
}


void nanopi_timbo::gpio_read()
{
	//GPIO read & control
	while(1){

		//1. read button
		map<int, int> gpio_map;
		for(auto& port:gpio_btn)
			gpio_map[port] = digitalRead(port);
		for(auto& port:gpio_sw)
			gpio_map[port] = digitalRead(port);


		//2. control (id selection : falling edge [high to low])
		if(_prev_gpio_map[BTN_ID_SEL] && !gpio_map[BTN_ID_SEL])
			cossb_log->log(log::loglevel::INFO, "Pushed ID Selection Button");
		//ID is changing..
		else if(!_prev_gpio_map[BTN_ID_SEL] && !gpio_map[BTN_ID_SEL]){
			if(_selected_id>=4)
				_selected_id = 0;
			wiringPiI2CWrite(_i2c_handle, ++_selected_id);
		}
		//stop changing.
		else if(!_prev_gpio_map[BTN_ID_SEL] && gpio_map[BTN_ID_SEL]){
			cossb_log->log(log::loglevel::INFO, fmt::format("Selected ID : {}", _selected_id));
		}

		//4. id setting (rising edge)
		if(!_prev_gpio_map[BTN_ID_SET] && gpio_map[BTN_ID_SET]){
			//publish message
			cossb::message msg(this, cossb::base::msg_type::REQUEST);
			msg.pack(gpio_map);
			cossb_log->log(log::loglevel::INFO, fmt::format("ID Setting : {}", _selected_id));
			cossb_broker->publish("nanopi_gpio_id_set", msg);
		}

		//5. read guidebook page
		if(!gpio_map[SW1]) move_page(1);
		else if(!gpio_map[SW2]) move_page(2);
		else if(!gpio_map[SW3]) move_page(3);
		else if(!gpio_map[SW4]) move_page(4);

		//6. trajectory play (rising edge)
		if(!_prev_gpio_map[BTN_TRJ_PLAY] && gpio_map[BTN_TRJ_PLAY]){
			cossb_log->log(log::loglevel::INFO, "Trajectory Play");
			cossb::message msg(this, cossb::base::msg_type::REQUEST);
			nlohmann::json _json_msg;
			_json_msg["command"] = "trajectory_play";
			_json_msg["page"] = _guidebook_page;
			msg.pack(_json_msg.dump());
			cossb_broker->publish("nanopi_websocket_read", msg);
		}

		_prev_gpio_map = gpio_map;

		//periodic
		if(boost::this_thread::interruption_requested()) break;
		boost::this_thread::sleep(boost::posix_time::milliseconds(500)); //read period = 500ms

	}
}

void nanopi_timbo::move_page(int page){

	if(_guidebook_page!=page){
		//move page for ebook
		cossb::message msg(this, cossb::base::msg_type::REQUEST);
		nlohmann::json _json_msg;
		_json_msg["command"] = "movepage";
		_json_msg["page"] = page;
		msg.pack(_json_msg.dump());
		cossb_log->log(log::loglevel::INFO, fmt::format("Change eBook Page : {}", page));
		cossb_broker->publish("websocket_write_msg",msg);
	}
	_guidebook_page = page;

}

