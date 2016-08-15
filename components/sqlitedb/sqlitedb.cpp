/*
 * sqlitedb.cpp
 *
 *  Created on: 2016. 8. 15.
 *      Author: hwang
 */

#include "sqlitedb.hpp"
#include <cossb.hpp>
#include <sqlite3.h>
#include <boost/filesystem.hpp>

USE_COMPONENT_INTERFACE(sqlitedb)

sqlitedb::sqlitedb()
:cossb::interface::icomponent(COMPONENT(sqlitedb)){

}

sqlitedb::~sqlitedb() {
	if(_db)
		sqlite3_close(_db);
}

bool sqlitedb::setup()
{
	_path_root = get_profile()->get(profile::section::property, "path").asString("./");
	cossb_log->log(log::loglevel::INFO, fmt::format("DB Root directory : {}", _path_root));

	return true;
}

bool sqlitedb::run()
{
	util::systime time;
	string _db_path = fmt::format("{}/{}_{}_{}_{}_{}_{}.sqlite3",_path_root,
				time.get_time()->ctm_year,time.get_time()->ctm_mon,time.get_time()->ctm_mday,
				time.get_time()->ctm_hour,time.get_time()->ctm_min,time.get_time()->ctm_sec);

	int rc = sqlite3_open(_db_path.c_str(), &_db);
	if(rc){
		cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot open database {}", _db_path));
		sqlite3_close(_db);
		return false;
	}
	else {
		cossb_log->log(log::loglevel::INFO, fmt::format("Opened database successfully", _db_path));
	}

	return true;
}

bool sqlitedb::stop()
{
	if(_db) {
		sqlite3_close(_db);
		_db_path.clear();
	}

	return true;
}

void sqlitedb::request(cossb::base::message* const msg)
{
	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST: {
		if(!msg->get_frame()->topic.compare("service/db/sqlite/query")) {
			if(msg->get_frame()->type==base::msg_type::REQUEST){
				if(!(*msg)["query"].is_null() && _db){
					//sqlite3_exec(_db,);
				}
			}
		}
	} break;
	case cossb::base::msg_type::DATA: break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::SIGNAL: break;
	}
}
