/*
 * timboprotocol.cpp
 *
 *  Created on: 2017. 11. 26.
 *      Author: byunghunhwang
 */



#include "timboprotocol.hpp"
#include <cossb.hpp>
#include <string>

using namespace std;

USE_COMPONENT_INTERFACE(timboprotocol)

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
	case cossb::base::msg_type::REQUEST: break;
	case cossb::base::msg_type::DATA: {
		try
		{
			vector<unsigned char> data = boost::any_cast<vector<unsigned char>>(*msg->get_data());
			_serial->write((const char*)data.data(), data.size());
			cossb_log->log(log::loglevel::INFO, fmt::format("Write {} byte(s) to the serial", data.size()));
		}
		catch(const boost::bad_any_cast&){
			cossb_log->log(log::loglevel::ERROR, "Invalid type casting");
		}
	} break;
	case cossb::base::msg_type::RESPONSE: break;
	}
}

}
