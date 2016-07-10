
#include "sqlite_db.hpp"
#include <cossb.hpp>
#include <sqlite3.h>
#include <boost/filesystem.hpp>

USE_COMPONENT_INTERFACE(sqlite_db)

sqlite_db::sqlite_db()
:cossb::interface::icomponent(COMPONENT(sqlite_db)){
	// TODO Auto-generated constructor stub

}

sqlite_db::~sqlite_db() {
	if(_db)
		sqlite3_close(_db);
}

bool sqlite_db::setup()
{
	_db_path = get_profile()->get(profile::section::property, "access").asString("db.sqlite");
	cossb_log->log(log::loglevel::INFO, fmt::format("Database : {}", _db_path));

	if(boost::filesystem::exists(_db_path.c_str())){
		int rc = sqlite3_open(_db_path.c_str(), &_db);
		if(rc!=SQLITE_OK){
			sqlite3_close(_db);
			cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot access database {}", _db_path));
			return false;
		}
	}
	else
		cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot find local database {}", _db_path));
	return true;
}

bool sqlite_db::run()
{

	return true;
}

bool sqlite_db::stop()
{
	return true;
}

void sqlite_db::request(cossb::base::message* const msg)
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
