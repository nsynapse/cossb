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
	void uart_read();
	void luart_read();
	void gpio_read();

	void trajectory_dump(int page, int module);

private:
	cossb::base::task _gpio_task;
	libserial* _uart = nullptr;
	libserial* _luart = nullptr;
	string _port;
	string _lport;
	bool _dumping = false;
	ofstream _dump_file;
	cossb::base::task _uart_task; //uart read task
	cossb::base::task _luart_task;

	deque<unsigned char> _dump_buffer;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_NANOPI_TIMBO_HPP_ */
