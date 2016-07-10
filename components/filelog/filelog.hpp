
#ifndef _COSSB_COMPONENT_FILELOG_HPP_
#define _COSSB_COMPONENT_FILELOG_HPP_


#include <base/interface.hpp>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

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
	std::map<string, ofstream*> _filemap;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_FILELOG_HPP_ */
