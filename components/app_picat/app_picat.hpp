/*
 * @brief	Application component
 */

#ifndef _COSSB_COMPONENT_APP_PICAT_HPP_
#define _COSSB_COMPONENT_APP_PICAT_HPP_

#include <interface/icomponent.hpp>
#include <map>

using namespace std;

class app_picat : public interface::icomponent {
public:
	app_picat();
	virtual ~app_picat();

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
	unsigned char encode(map<string, double> emotion);

private:
	int _gpio_trigger = -1;
	unsigned char _prev_read = 0x00;
	map<string, double> _emotion;


};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_APP_PICAT_HPP_ */
