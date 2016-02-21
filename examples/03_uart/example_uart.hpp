/**
 * @file		example_uart.hpp
 * @brief		UART Component Example
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2016. 2. 2
 * @details	UART component
 */

#ifndef _COSSB_EXAMPLE_UART_HPP_
#define _COSSB_EXAMPLE_UART_HPP_

#include <base/interface.hpp>

using namespace cossb;

class example_uart : public interface::icomponent {
public:
	example_uart();
	virtual ~example_uart();

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
	/**
	 * @brief	write task function
	 */
	void do_write();

private:
	cossb::base::task _write_task;

};

COMPONENT_EXPORT

#endif /* _COSSB_EXAMPLE_UART_HPP_ */
