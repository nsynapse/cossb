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
#include <fstream>
#include <deque>
#include "libserial.hpp"

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
	// UART read function for wireless
	void wireless_uart_read();

	//UART read function for wired
	void wired_uart_read();

	//GPIO control function for read
	void gpio_read();

private:
	//gpio control task
	cossb::base::task _gpio_task;

	//async serial read callback function
	cossb::base::task _wl_uart_read_task;
	cossb::base::task _w_uart_read_task;

	//serial communication instance for wireless
	libserial* _wl_uart = nullptr;

	//serial communication instance for wired
	libserial* _w_uart = nullptr;

	//serial port name(wireless)
	string _wl_port;

	//serial port name(wired)
	string _w_port;

	//previous gpio map
	map<int, int> _prev_gpio_map;
	int _led_index = 0;


	bool _dumping = false;
	ofstream _dump_file;
	deque<unsigned char> _dump_buffer;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_NANOPI_TIMBO_HPP_ */
