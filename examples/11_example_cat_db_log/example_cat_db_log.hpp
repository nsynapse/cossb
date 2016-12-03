

#ifndef _COSSB_EXAMPLE_CAT_DB_LOG_HPP_
#define _COSSB_EXAMPLE_CAT_DB_LOG_HPP_

#include <base/interface.hpp>
#include <string>

using namespace std;

class sqlite3;
class example_cat_db_log : public interface::icomponent {
public:
	example_cat_db_log();
	virtual ~example_cat_db_log();

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
	void write();

private:
	string _dbname;
	base::task _task;

};

COMPONENT_EXPORT

#endif /* _COSSB_EXAMPLE_CAT_DB_LOG_HPP_ */
