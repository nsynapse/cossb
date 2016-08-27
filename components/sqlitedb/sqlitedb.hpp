
#ifndef _COSSB_COMPONENT_SQLITEDB_HPP_
#define _COSSB_COMPONENT_SQLITEDB_HPP_

#include <base/interface.hpp>
#include <string>
#include <util/localtime.hpp>
#include <sqlite3.h>

using namespace cossb;
using namespace std;

class sqlitedb : public interface::icomponent {
public:
	sqlitedb();
	virtual ~sqlitedb();

	/**
	 * @brief	setup interface function
	 */
	bool setup();

	/**
	 * @brief	run interface function
	 */
	bool run();

	/**
	 * @brief	stop interface function
	 */
	bool stop();

	/**
	 * @brief	request interface function
	 */
	void request(cossb::base::message* const msg);

private:
	util::systime _time;
	string _db_path;
	string _path_root;
	sqlite3* _db = nullptr;
	sqlite3_stmt* _stmt = nullptr;	//sqlite statement

};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_SQLITE_DB_HPP_ */
