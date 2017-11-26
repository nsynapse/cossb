/*
 * timboprotocol.hpp
 *
 *  Created on: 2017. 11. 26.
 *      Author: byunghunhwang
 */

#ifndef COMPONENTS_TIMBOPROTOCOL_TIMBOPROTOCOL_HPP_
#define COMPONENTS_TIMBOPROTOCOL_TIMBOPROTOCOL_HPP_


#include <interface/icomponent.hpp>
#include <base/task.hpp>

using namespace cossb;

class timboprotocol : public interface::icomponent {
public:
	timboprotocol();
	virtual ~timboprotocol();

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

};

COMPONENT_EXPORT


#endif /* COMPONENTS_TIMBOPROTOCOL_TIMBOPROTOCOL_HPP_ */
