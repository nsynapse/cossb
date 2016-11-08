
#ifndef _COSSB_COMPONENT_FILELOG_HPP_
#define _COSSB_COMPONENT_FILELOG_HPP_

/**
 * @brief	logging into text file
 * @detail	all the incoming data saves into the single text file
 */


#include <interface/icomponent.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <util/localtime.hpp>

using namespace std;
using namespace cossb;

class filelog : public interface::icomponent {
public:
	filelog();
	virtual ~filelog();

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
	ofstream _file;
	string _path;
	util::systime _time;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_FILELOG_HPP_ */
