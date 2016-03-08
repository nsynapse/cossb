
#include "example_edison_i2c.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(example_edison_i2c)

example_edison_i2c::example_edison_i2c()
:cossb::interface::icomponent(COMPONENT(example_edison_i2c))
{

}

example_edison_i2c::~example_edison_i2c()
{

}

bool example_edison_i2c::setup()
{
	if(!_task)
		create_task(example_edison_i2c::write);

	return true;
}

bool example_edison_i2c::run()
{
	return true;
}

bool example_edison_i2c::stop()
{
	destroy_task(_task);

	return true;
}

void example_edison_i2c::request(cossb::base::message* const msg)
{

}

void example_edison_i2c::write()
{
	try {
		while(1) {
			cossb::base::message msg(this, base::msg_type::REQUEST);

			msg["data"] = { 0x01, 0x02, 0x03 };
			cossb_broker->publish("example_i2c_write", msg);
			cossb_log->log(cossb::log::loglevel::INFO, fmt::format("Send I2C Message : {}",msg.show()));

			boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

		}
		} catch(cossb::broker::exception& e) {
			cossb_log->log(cossb::log::loglevel::ERROR, fmt::format("{}", e.what()).c_str());
		}
}


