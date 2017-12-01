/*
 * @brief	Application component for Timbo ebook
 */

#ifndef _COSSB_COMPONENT_APP_TIMBO_HPP_
#define _COSSB_COMPONENT_APP_TIMBO_HPP_

#include <interface/icomponent.hpp>
#include <map>

using namespace std;

class app_timbo : public interface::icomponent {
public:
	app_timbo();
	virtual ~app_timbo();

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
	void subscribe(cossb::message* const msg);

private:

	void load_motion(const char* filename);

	void run_motion();

};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_APP_TIMBO_HPP_ */
