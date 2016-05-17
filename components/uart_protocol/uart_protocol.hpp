/*
 * protocol.hpp
 *
 *  Created on: 2016. 5. 17.
 *      Author: hwang
 */

#ifndef _COSSB_COMPONENT_PROTOCOL_HPP_
#define _COSSB_COMPONENT_PROTOCOL_HPP_

#include <base/interface.hpp>
#include <deque>

using namespace cossb;

class uart_protocol : public interface::icomponent {
public:
	uart_protocol();
	virtual ~uart_protocol();

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
	std::deque<unsigned char> _queue;

};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_PROTOCOL_HPP_ */
