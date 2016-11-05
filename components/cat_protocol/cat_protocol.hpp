/*
 * protocol.hpp
 *
 *  Created on: 2016. 5. 17.
 *      Author: hwang
 */

#ifndef _COSSB_COMPONENT_CAT_PROTOCOL_HPP_
#define _COSSB_COMPONENT_CAT_PROTOCOL_HPP_

#include <base/interface.hpp>
#include <deque>

using namespace cossb;

class cat_protocol : public interface::icomponent {
public:
	cat_protocol();
	virtual ~cat_protocol();

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
	string _websocket_uri;

};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_CAT_PROTOCOL_HPP_ */
