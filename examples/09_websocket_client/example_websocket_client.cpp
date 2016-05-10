
#include "example_websocket_client.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(example_websocket_client)

example_websocket_client::example_websocket_client()
:cossb::interface::icomponent(COMPONENT(example_websocket_client))
{
	// TODO Auto-generated constructor stub

}

example_websocket_client::~example_websocket_client() {
	// TODO Auto-generated destructor stub
}


bool example_websocket_client::setup()
{
	if(!_task)
		create_task(example_websocket_client::write);

	return true;
}

bool example_websocket_client::run()
{
	return true;
}

bool example_websocket_client::stop()
{
	destroy_task(_task);

	return true;
}

void example_websocket_client::request(cossb::base::message* const msg)
{

}

void example_websocket_client::write()
{
	while(1) {
		try {
			cossb::base::message msg(this, base::msg_type::REQUEST);

			msg["data"] = { 0x01, 0x02, 0x0f };
			cossb_broker->publish("example_websocket_write", msg);
			//cossb_log->log(cossb::log::loglevel::INFO, fmt::format("Websocket Write Message : {}",msg.show()));
			boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		} catch(thread_interrupted&) {
			break;
		}
	}
}
