/**
 * @file		tcpserver.hpp
 * @brief		TCP Server Component Example
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details		TCP Server component
 */

#ifndef _COSSB_EXAMPLE_TCPSERVER_HPP_
#define	_COSSB_EXAMPLE_TCPSERVER_HPP_

#include <base/interface.hpp>
#include <net/tcp.hpp>
using namespace cossb;

class tcpserver : public interface::icomponent {
public:
	tcpserver();
	virtual ~tcpserver();

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
	net::tcp::server* _server = nullptr;
};

COMPONENT_EXPORT

#endif /* _COSSB_EXAMPLE_TCPSERVER_HPP_ */
