
#include "timboprotocol.hpp"
#include <cossb.hpp>
#include <string>

using namespace std;

USE_COMPONENT_INTERFACE(timboprotocol)

#define HEADER	0x55
#define END		0xAA
#define RECORD	0x02
#define PLAY		0x03
#define STOP		0x04
#define PING		0x24

timboprotocol::timboprotocol()
:cossb::interface::icomponent(COMPONENT(timboprotocol)){
	// TODO Auto-generated constructor stub

}

timboprotocol::~timboprotocol() {

}

bool timboprotocol::setup()
{

	return true;
}

bool timboprotocol::run()
{

	return true;
}

bool timboprotocol::stop()
{

	return true;
}

void timboprotocol::subscribe(cossb::message* const msg)
{
	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST:
		try {
			unsigned char data = boost::any_cast<unsigned char>(*msg->get_data());
			switch(data){
			case RECORD: _record(); break;
			case PLAY: _play(); break;
			case STOP: _stop(); break;
			case PING: _ping(); break;
			}

		} catch(const boost::bad_any_cast&){
			cossb_log->log(log::loglevel::ERROR, "Request : Invalid type casting");
		}
		break;
	case cossb::base::msg_type::DATA: {

		//timbo protocol read service (data will be coming from UART component)
		try
		{
			vector<unsigned char> data = boost::any_cast<vector<unsigned char>>(*msg->get_data());

			//insert data into the end of buffer
			_buffer.insert(_buffer.end(), data.begin(), data.end());

			//remove invalid data (first byte must be 0x55)
			while(!_buffer.empty()){
				if(_buffer.front()!=HEADER)
					_buffer.pop_front();
				else
					break;
			}

			//extract single packet
			while(_buffer.size()>=6){
				int length = _buffer[1];
				//valid packet
				if(_buffer[2+length]==END){
					vector<unsigned char> packet;
					packet.assign(_buffer.begin(), _buffer.begin()+_buffer[1]+3);
					for(int i=0;i<(int)packet.size();i++)
						_buffer.pop_front(); //remove assigned packet bytes length

					//publish the aligned data
					cossb::message msg(this, cossb::base::msg_type::DATA);
					msg.pack(packet);
					cossb_broker->publish("timbo_protocol_write", msg);
					cossb_log->log(log::loglevel::INFO, fmt::format("Published {}bytes data", packet.size()));
				}
			}
		}
		catch(const boost::bad_any_cast&){
			cossb_log->log(log::loglevel::ERROR, "Data : Invalid type casting");
		}
	} break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::EVENT: break;
	}
}

void timboprotocol::_record() {
	unsigned char data[] = {0x55,0x03,0x0F,0x02,0x00,0xAA};
	vector<unsigned char> packet(data, data+sizeof(data));
	cossb::message msg(this, cossb::base::msg_type::DATA);
	msg.pack(packet);
	cossb_broker->publish("timbo_protocol_write", msg);
	cossb_log->log(log::loglevel::INFO, "Record");
}

void timboprotocol::_play() {
	unsigned char data[] = {0x55,0x03,0x0F,0x03,0x00,0xAA};
	vector<unsigned char> packet(data, data+sizeof(data));
	cossb::message msg(this, cossb::base::msg_type::DATA);
	msg.pack(packet);
	cossb_broker->publish("timbo_protocol_write", msg);
	cossb_log->log(log::loglevel::INFO, "Play");
}

void timboprotocol::_stop() {
	unsigned char data[] = {0x55,0x03,0x0F,0x04,0x00,0xAA};
	vector<unsigned char> packet(data, data+sizeof(data));
	cossb::message msg(this, cossb::base::msg_type::DATA);
	msg.pack(packet);
	cossb_broker->publish("timbo_protocol_write", msg);
	cossb_log->log(log::loglevel::INFO, "Stop");
}

void timboprotocol::_ping() {
	unsigned char data[] = {0x55,0x03,0x0F,0x24,0x00,0xAA};
	vector<unsigned char> packet(data, data+sizeof(data));
	cossb::message msg(this, cossb::base::msg_type::DATA);
	msg.pack(packet);
	cossb_broker->publish("timbo_protocol_write", msg);
	cossb_log->log(log::loglevel::INFO, "Ping");
}
