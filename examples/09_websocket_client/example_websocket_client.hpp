/**
 * @file		example_websocket_client.hpp
 * @brief		Websocket Client Example Componet
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2016. 4. 20
 * @details		publish json data to websocket client component
 */

#ifndef _COSSB_EXAMPLE_WEBSOCKET_CLIENT_HPP_
#define _COSSB_EXAMPLE_WEBSOCKET_CLIENT_HPP_

#include <base/interface.hpp>
#include <string>

using namespace std;
using namespace cossb;

class example_websocket_client : public interface::icomponent {
public:
	example_websocket_client();
	virtual ~example_websocket_client();

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
	void write();

private:
	cossb::base::task _task;

	std::string _url_prefix;
};

COMPONENT_EXPORT

#endif /* _COSSB_EXAMPLE_WEBSOCKET_CLIENT_HPP_ */
