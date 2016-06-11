
#include "cat_protocol.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(cat_protocol)


cat_protocol::cat_protocol()
:cossb::interface::icomponent(COMPONENT(cat_protocol)){
	// TODO Auto-generated constructor stub

}

cat_protocol::~cat_protocol() {

}

bool cat_protocol::setup()
{
	return true;
}

bool cat_protocol::run()
{
	return true;
}

bool cat_protocol::stop()
{


	return true;
}

void cat_protocol::request(cossb::base::message* const msg)
{
	switch(msg->get_frame()->type)
	{
		case cossb::base::msg_type::REQUEST:
		{
			if(!(*msg)["data"].is_null()){
				if((*msg)["data"].is_array()){
					//insert
					_queue.insert(_queue.end(),(*msg)["data"].begin(),(*msg)["data"].end());

					//alignment
					while(_queue.size()>=4){
						try {
							if((_queue[0]&0xff) && (_queue[1]&0xff)) {
								//enought data to process
								if((_queue.size()>=(unsigned int)_queue[3]+4)) {
									base::message msg(this, base::msg_type::REQUEST);
									msg["id"] = _queue[2];
									msg["error"] = _queue[4];
									for(unsigned int i=0;i<(unsigned int)_queue[3]-2;i++)
										msg["value"].push_back(_queue[i+5]);
									_queue.erase(_queue.begin(), _queue.begin()+(unsigned int)_queue[3]+4);

									cossb_broker->publish("cat_protocol_align", msg);
									cossb_log->log(log::loglevel::INFO, "Message is aligned and published.");
								}
								else
									break;
							}
							else
								_queue.pop_front();
						}
						catch(thread_interrupted&){
							break;
						}
					}
					boost::this_thread::sleep(boost::posix_time::milliseconds(0));
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


