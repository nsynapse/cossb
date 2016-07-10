/*
 * filelog.cpp
 *
 *  Created on: 2016. 7. 10.
 *      Author: hwang
 */

#include "filelog.hpp"

USE_COMPONENT_INTERFACE(filelog)

filelog::filelog()
:cossb::interface::icomponent(COMPONENT(filelog)){
	// TODO Auto-generated constructor stub

}

filelog::~filelog() {
	for(auto fp:_filemap){
		fp.second->close();
		delete fp.second;
	}
	_filemap.clear();
}

bool filelog::setup()
{
	return true;
}

bool filelog::run()
{
	return true;
}

bool filelog::stop()
{
	return true;
}

void filelog::request(cossb::base::message* const msg)
{
	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST: {
		if(!msg->get_frame()->topic.compare("service/filelog/write")){
			if(!(*msg)["file"].is_null() && (*msg)["file"].is_string()){
				map<string, ofstream*>::iterator itr = _filemap.find((*msg)["file"]);
				if(itr!=_filemap.end()){
					if((*itr).second->is_open()){
						(*(*itr).second) << (*msg)["data"] << endl;
					}
				}
				else {
					string file = (*msg)["filepath"];
					(*msg)["filepath"] = new ofstream(file);
				}
			}
		}
	} break;
	case cossb::base::msg_type::DATA: break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::SIGNAL: break;
	}
}

