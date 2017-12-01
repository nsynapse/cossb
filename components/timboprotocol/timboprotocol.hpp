/*
 * timboprotocol.hpp
 *
 *  Created on: 2017. 11. 26.
 *      Author: byunghunhwang
 */

// this component works for timbo protocol alignment

#ifndef COMPONENTS_TIMBOPROTOCOL_TIMBOPROTOCOL_HPP_
#define COMPONENTS_TIMBOPROTOCOL_TIMBOPROTOCOL_HPP_


#include <interface/icomponent.hpp>
#include <base/task.hpp>
#include <deque>

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

private:
	/*
	 * @brief	protocol matching function
	 */
	void _record();
	void _stop();
	void _play();
	void _ping();

private:
	deque<unsigned char> _buffer;

};

COMPONENT_EXPORT


#endif /* COMPONENTS_TIMBOPROTOCOL_TIMBOPROTOCOL_HPP_ */
