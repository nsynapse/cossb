/*
 * filelog.cpp
 *
 *  Created on: 2016. 7. 10.
 *      Author: hwang
 */

#include "filelog.hpp"
#include <cossb.hpp>
#include <base/message.hpp>

USE_COMPONENT_INTERFACE(filelog)

filelog::filelog()
:cossb::interface::icomponent(COMPONENT(filelog)){
	// TODO Auto-generated constructor stub

}

filelog::~filelog() {
	_file.close();
}

bool filelog::setup()
{
	_path = get_profile()->get(profile::section::property, "path").asString("./");

	return true;
}

bool filelog::run()
{
	if(!_file.is_open()) {
		string fullpath = _path+_time.current()+string(".log");
		_file.open(fullpath.c_str(), std::ofstream::in|std::ofstream::app);
	}

	return true;
}

bool filelog::stop()
{
	if(_file.is_open()) {
		_file.flush();
		_file.close();
	}

	return true;
}

void filelog::request(cossb::base::message* const msg)
{
	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST:
	{
		if(msg->exist("value")){
			cossb_log->log(log::loglevel::INFO, fmt::format("Write to logfile : {} ", (*msg)["value"].dump()));
			if(_file.is_open()){
				_file << (*msg)["value"].dump();
				_file.flush();
			}
			else
				cossb_log->log(log::loglevel::ERROR, "Log File did not open");
		}

		/*if(!msg->get_frame()->topic.compare("service/filelog/write")) {
			if(!(*msg)["data"].is_null() && (*msg)["data"].is_array()) {

				if(!_file.is_open()){
					_path = _path + _time.current() + string(".txt");
					_file.open(_path.c_str(), ios_base::out);
				}

				for(auto& element : (*msg).data) {
				  ofstream << element;
				}
			}
		}*/
	} break;
	case cossb::base::msg_type::DATA: break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::SIGNAL: break;
	}
}

