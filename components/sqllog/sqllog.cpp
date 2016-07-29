#include "sqllog.hpp"
#include <sqlite3.h>

USE_COMPONENT_INTERFACE(sqllog)

sqllog::sqllog()
:cossb::interface::icomponent(COMPONENT(sqllog)){
	// TODO Auto-generated constructor stub

}

sqllog::~sqllog() {
}

bool sqllog::setup()
{

	return true;
}

bool sqllog::run()
{
	return true;
}

bool sqllog::stop()
{
	return true;
}

void sqllog::request(cossb::base::message* const msg)
{
	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST:
	{

	} break;
	case cossb::base::msg_type::DATA: break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::SIGNAL: break;
	}
}

