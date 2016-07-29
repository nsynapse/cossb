
#ifndef _COSSB_COMPONENT_SQLLOG_HPP_
#define _COSSB_COMPONENT_SQLLOG_HPP_

/**
 * @brief	logging into sqlite3 database
 */

#include <base/interface.hpp>


using namespace std;
using namespace cossb;

class sqlite3;
class sqllog : public interface::icomponent {
public:
	sqllog();
	virtual ~sqllog();

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
	sqlite3* _db = nullptr;
	string _path;
};


COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_SQLLOG_HPP_ */
