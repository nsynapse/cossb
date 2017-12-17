/*
 * nanopi_timbo.hpp
 *
 *  Created on: Dec 10, 2017
 *      Author: hwangvm
 */

#ifndef _COSSB_COMPONENT_NANOPI_TIMBO_HPP_
#define _COSSB_COMPONENT_NANOPI_TIMBO_HPP_


#include <interface/icomponent.hpp>
#include <base/task.hpp>
#include <map>
#include <string>

using namespace std;


class nanopi_timbo : public interface::icomponent  {
public:
	nanopi_timbo();
	virtual ~nanopi_timbo();

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
	void uart_read();
	void gpio_read();

	//send trajectory

private:
	//map<int, bool> _gpio_port_map; //true output, false input
	//map<int, int> _gpio_port_read;
	cossb::base::task _gpio_task;
	string _port;
	cossb::base::task _uart_task; //uart read task
	int fd = -1;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_NANOPI_TIMBO_HPP_ */
