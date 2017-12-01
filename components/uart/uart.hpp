/**
 * @file		uart.hpp
 * @brief	UART Component
 * @author	Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 	2016. 2. 2
 * @details	common UART Component
 */

#ifndef _COSSB_COMPONENT_UART_HPP_
#define _COSSB_COMPONENT_UART_HPP_

#include <interface/icomponent.hpp>
#include <base/task.hpp>
#include "libserial.hpp"

using namespace cossb;

class uart : public interface::icomponent {
public:
	uart();
	virtual ~uart();

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
	/**
	 * @brief	read from serial port
	 */
	void read();

private:
	libserial* _uart = nullptr;
	string _port;
	cossb::base::task _read_task;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_UART_HPP_ */
