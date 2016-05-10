/*
 * wsclient.hpp
 *
 *  Created on: 2016. 4. 20.
 *      Author: hwang
 */

#ifndef _COSSB_COMPONENT_WEBSOCKET_CLIENT_HPP_
#define _COSSB_COMPONENT_WEBSOCKET_CLIENT_HPP_

#include <base/interface.hpp>
#include "easywsclient.hpp"
#include "easywsclient.cpp"
using namespace cossb;
using easywsclient::WebSocket;

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

private:
	easywsclient::WebSocket::pointer _client = nullptr;

	base::task _socket_task;

private:
	void socket_control();

};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_WEBSOCKET_CLIENT_HPP_ */
