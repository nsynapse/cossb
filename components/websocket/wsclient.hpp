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
#include <vector>
#include <map>
#include <mutex>

using namespace cossb;
using easywsclient::WebSocket;
using namespace std;

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
	void subscribe(cossb::message* const msg);

private:
	base::task _socket_task;
	//map<string, easywsclient::WebSocket::pointer> _client_map;
	easywsclient::WebSocket::pointer _client = nullptr;
	std::mutex _lock;
	//map<string, bool> _reconnect;

private:
	void read();

};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_WEBSOCKET_CLIENT_HPP_ */
