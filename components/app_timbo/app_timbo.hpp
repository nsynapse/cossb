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

	unsigned char _group_id[5] = {0x00, };

private:
	void key_id_setting(int value);	//press key for id setting
	void key_id_select(int value);	//press key for id select
	void key_send_trajectory(int value); 	//press key for trajectory send
	void run_motion(int contents);
	void timbo_record();
	void timbo_play();
	void timbo_stop();
	void timbo_ping();

};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_APP_TIMBO_HPP_ */
