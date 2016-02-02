/**
 * @file		serial.hpp
 * @brief		serial Component Example
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2016. 2. 2
 * @details	serial component
 */

#ifndef _COSSB_COMPONENT_SERIAL_HPP_
#define _COSSB_COMPONENT_SERIAL_HPP_

#include <base/interface.hpp>
#include "libserial.hpp"

using namespace cossb;

class serial : public interface::icomponent {
public:
	serial();
	virtual ~serial();

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
	 * @brief	read from serial port
	 */
	void read();

private:
	libserial* _serial = nullptr;
	cossb::base::task _read_task;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_SERIAL_HPP_ */
