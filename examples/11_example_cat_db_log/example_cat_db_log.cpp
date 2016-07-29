
#include "example_cat_db_log.hpp"
#include <cossb.hpp>

USE_COMPONENT_INTERFACE(example_cat_db_log)

example_cat_db_log::example_cat_db_log()
:cossb::interface::icomponent(COMPONENT(example_cat_db_log)) {

}

example_cat_db_log::~example_cat_db_log() {

}

bool example_cat_db_log::setup()
{
	return true;
}

bool example_cat_db_log::run()
{

	return true;
}

bool example_cat_db_log::stop()
{

	return true;
}

void example_cat_db_log::request(cossb::base::message* const msg)
{
	switch(msg->get_frame()->type)
	{
		case cossb::base::msg_type::REQUEST:
		{
			cossb_log->log(log::loglevel::INFO, fmt::format("Request for DB : {}", msg->raw()));
		} break;
		case cossb::base::msg_type::DATA: break;
		case cossb::base::msg_type::SIGNAL: break;
		default:
			cossb_log->log(log::loglevel::INFO, "Received message has unsupported type.");
	}
}
