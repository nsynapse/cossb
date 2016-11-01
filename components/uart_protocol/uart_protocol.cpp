
#include "uart_protocol.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(uart_protocol)


uart_protocol::uart_protocol()
:cossb::interface::icomponent(COMPONENT(uart_protocol)){
	// TODO Auto-generated constructor stub

}

uart_protocol::~uart_protocol() {

}

bool uart_protocol::setup()
{
	return true;
}

bool uart_protocol::run()
{
	return true;
}

bool uart_protocol::stop()
{


	return true;
}

void uart_protocol::request(cossb::base::message* const msg)
{
	switch(msg->get_frame()->type)
	{
		case cossb::base::msg_type::REQUEST:
		{
			if(!msg->get_frame()->topic.compare("service/uart/read")) {
				if((*msg)["data"].is_array()) {

					_queue.insert(_queue.end(),(*msg)["data"].begin(),(*msg)["data"].end());

					while(_queue.size()>=4){
						if((_queue[0]&0xff) && (_queue[1]&0xff)){
							//enough data to process
							if(((unsigned int)_queue[3]+4)>=_queue.size()){
								//do data validation check (checksum)
								//here

								//if valid, create message
								base::message msg(this, base::msg_type::DATA);
								msg["id"] = _queue[2];
								msg["length"] = (unsigned int)_queue[3];
								msg["instruction"] = _queue[4];
								msg["parameter"] = std::vector<unsigned char>(_queue.begin()+5, _queue.begin()+(unsigned int)_queue[3]);

								cossb_broker->publish("protocol_read", msg);
								cossb_log->log(log::loglevel::INFO, fmt::format("published processed protocol data {}", msg.raw()));
								_queue.erase(_queue.begin(), _queue.begin()+(unsigned int)_queue[3]+4);
							}
						}
						else
							_queue.pop_front();
					} //end while
				}
			}
		}
			break;
		case cossb::base::msg_type::DATA: break;
		case cossb::base::msg_type::SIGNAL: break;
		default:
			cossb_log->log(log::loglevel::INFO, "Received message has unsupported type.");
	}
}


