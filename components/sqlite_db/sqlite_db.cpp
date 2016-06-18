
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
	_dbname = get_profile()->get(profile::section::property, "targetdb").asString("db.sqlite");
	if(boost::filesystem::exists(_dbname.c_str())){
		int rc = sqlite3_open(_dbname.c_str(), &_db);
		if(rc){
			cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot access database {}", _dbname));
			return false;
		}
	}
	else
		cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot find local database {}", _dbname));
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
	} break;
	case cossb::base::msg_type::DATA: break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::SIGNAL: break;
	}
}
