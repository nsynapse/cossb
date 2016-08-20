
#include "example_cat_monitoring.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(example_cat_monitoring)

example_cat_monitoring::example_cat_monitoring()
:cossb::interface::icomponent(COMPONENT(example_cat_monitoring))
{
	// TODO Auto-generated constructor stub

}

example_cat_monitoring::~example_cat_monitoring() {
	// TODO Auto-generated destructor stub
}


bool example_cat_monitoring::setup()
{

	return true;
}

bool example_cat_monitoring::run()
{
	if(!_task)
		create_task(example_cat_monitoring::write);

	return true;
}

bool example_cat_monitoring::stop()
{
	destroy_task(_task);

	return true;
}

void example_cat_monitoring::request(cossb::base::message* const msg)
{
	//cossb_log->log(log::loglevel::INFO, fmt::format("Message : {}", msg->raw()));

	//for test
	//cossb::base::message control_msg(this, base::msg_type::REQUEST);
	//control_msg = msg;
	cossb_broker->publish("example_cat_compcontrol", *msg);



	switch(msg->get_frame()->type)
	{
		case cossb::base::msg_type::REQUEST:
		{
			try {
				//if 'id' has a value
				if(!(*msg)["id"].is_null()){
					if((*msg)["id"].is_number()){
						//read id value as int
						int id = (*msg)["id"].get<int>();
						cossb_log->log(log::loglevel::INFO, fmt::format("Message ID : {}", id));
					}

					if(!(*msg)["list"].is_null()){
						if((*msg)["list"].is_array()){
							//std::vector<int> arr = (*msg)["list"];	//correct
							std::vector<bool> arr = (*msg)["list"];	//error!!
							for(int v:arr)
								cout << v << "\t";
							cout << endl;
						}
					}
				}
			}
			catch(std::exception& e){
				cossb_log->log(log::loglevel::ERROR, fmt::format("message error : {}", e.what()));
			}
		} break;
		case cossb::base::msg_type::DATA: break;
		case cossb::base::msg_type::SIGNAL: break;
		default:
			cossb_log->log(log::loglevel::INFO, "Received message has unsupported type.");
	}
}

void example_cat_monitoring::write()
{
	static unsigned long try_count = 1;
	static char id = 0x01;
	while(1) {
		try {
			cossb::base::message msg(this, base::msg_type::REQUEST);

			//test protocol for monitoring test
			//it will be converted as [ 0xff | 0xff | id | length | error | value | checksum ]
			static unsigned char value = 0;
			msg["data"] = {0xff, 0xff, 0x01, 0x03, 0x00, value++, 0xdb };
			cossb_broker->publish("example_cat_push", msg);

			if(value>=255)
				value=0;

			//cossb_log->log(cossb::log::loglevel::INFO, fmt::format("[{}] Send Test Message : {}",try_count++, msg.raw()));
			boost::this_thread::sleep(boost::posix_time::milliseconds(500));

			id++;
			if(id>0x05){
				id=0x01;
			}

		} catch(thread_interrupted&) {
			break;
		}
	}
}
