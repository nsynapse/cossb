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

	//GPIO read function for I2C
	void gpio_read();

	//IR read function
	void ir_read();

	//page move
	void move_page(int page);

	void ir_command(const char* command, int page);

private:
	//gpio control task
	cossb::base::task _led_task;
	cossb::base::task _ir_task;

	//async serial read callback function
	cossb::base::task _wl_uart_read_task;
	cossb::base::task _w_uart_read_task;

	//serial communication instance for wireless
	libserial* _wl_uart = nullptr;

	//serial communication instance for wired
	libserial* _w_uart = nullptr;

	//serial port name
	string _wl_port;
	string _w_port;

	//previous gpio map
	map<int, int> _prev_gpio_map;
	int _selected_id = 0;
	int _guidebook_page = 5;


	bool _dumping = false;
	ofstream _dump_file;
	deque<unsigned char> _dump_buffer;

	//i2c address
	unsigned char _i2c_address = 0x00;
	int _i2c_handle = -1;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_NANOPI_TIMBO_HPP_ */
