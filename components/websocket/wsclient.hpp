/*
 * wsclient.hpp
 *
 *  Created on: 2016. 4. 20.
 *      Author: hwang
 */

#ifndef _COSSB_COMPONENT_WEBSOCKET_CLIENT_HPP_
#define _COSSB_COMPONENT_WEBSOCKET_CLIENT_HPP_

#include <base/interface.hpp>

using namespace cossb;

class wsclient : public interface::icomponent {
public:
	wsclient();
	virtual ~wsclient();

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
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_WEBSOCKET_CLIENT_HPP_ */
