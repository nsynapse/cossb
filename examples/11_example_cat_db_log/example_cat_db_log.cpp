
#include "example_cat_db_log.hpp"
#include <cossb.hpp>
#include <sqlite3.h>
#include <boost/filesystem.hpp>

USE_COMPONENT_INTERFACE(example_cat_db_log)

example_cat_db_log::example_cat_db_log()
:cossb::interface::icomponent(COMPONENT(example_cat_db_log)) {

}

example_cat_db_log::~example_cat_db_log() {
	sqlite3_close(_db);
}

bool example_cat_db_log::setup()
{
	_dbname = get_profile()->get(profile::section::property, "db").asString("db.sqlite");
	if(boost::filesystem::exists(_dbname.c_str())){
		int rc = sqlite3_open(_dbname.c_str(), &_db);
		if(rc){
			cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot access database {}", _dbname));
			return false;
		}
	}

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
			if(!(*msg)["id"].is_null() && !(*msg)["value"].is_null()){
				if((*msg)["value"].is_array()){
					std::vector<unsigned char> raw = (*msg)["value"];
					//store to database
					//code here

					cossb_log->log(log::loglevel::INFO, fmt::format("Saved : {}", (*msg)["value"].dump()));
				}
			}
		} break;
		case cossb::base::msg_type::DATA: break;
		case cossb::base::msg_type::SIGNAL: break;
		default:
			cossb_log->log(log::loglevel::INFO, "Received message has unsupported type.");
	}
}
