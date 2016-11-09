

#ifndef _COSSB_EXAMPLE_FILELOG_HPP_
#define _COSSB_EXAMPLE_FILELOG_HPP_

#include <base/interface.hpp>
#include <string>

using namespace std;

class example_filelog : public interface::icomponent {
public:
	example_filelog();
	virtual ~example_filelog();

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
	base::task _task;

	void write();

};

COMPONENT_EXPORT

#endif /* _COSSB_EXAMPLE_FILELOG_HPP_ */
