
#include "../04_messageout/example_messageout.hpp"

#include <cossb.hpp>

USE_COMPONENT_INTERFACE(example_messageout)

example_messageout::example_messageout()
:cossb::interface::icomponent(COMPONENT(example_messageout))
{
	// TODO Auto-generated constructor stub

}

example_messageout::~example_messageout() {
	// TODO Auto-generated destructor stub
}

bool example_messageout::setup()
{

	return true;
}

bool example_messageout::run()
{
	if(!_task)
		create_task(example_messageout::do_task);

	return true;
}

bool example_messageout::stop()
{
	destroy_task(_task);

	return true;
}

void example_messageout::request(cossb::base::message* const msg)
{

}

void example_messageout::do_task()
{
	try {
	while(1) {
		cossb::base::message msg(this, base::msg_type::REQUEST);
		msg["print"] = "this is example message";
		cossb_broker->publish("service/messageout", msg);

		//cossb_log->log(cossb::log::loglevel::INFO, fmt::format("{}",msg.show()));
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

	}
	} catch(cossb::broker::exception& e) {
		cossb_log->log(cossb::log::loglevel::ERROR, fmt::format("{}", e.what()).c_str());
	}
}
