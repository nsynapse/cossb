/**
 * @file		sqlite_db.hpp
 * @brief		simple sqlite database component
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2016. 2. 2
 * @details	read/write/search query into the sqlite database
 */

#ifndef _COSSB_COMPONENT_SQLITE_DB_HPP_
#define _COSSB_COMPONENT_SQLITE_DB_HPP_

#include <base/interface.hpp>
#include <string>

using namespace cossb;
using namespace std;

class sqlite3;
class sqlite_db : public interface::icomponent {
public:
	sqlite_db();
	virtual ~sqlite_db();

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
	string _dbname;
	sqlite3* _db = nullptr;

};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_SQLITE_DB_HPP_ */
