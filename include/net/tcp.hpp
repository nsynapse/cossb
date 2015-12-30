/**
 * @file		tcp.hpp
 * @brief		tcp protocol class
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 10. 3
 * @details		TCP
 */

#include <net/sock.hpp>
#include <interface/icomm.hpp>

namespace cossb {
namespace net {
namespace tcp {

/**
 * @brief	tcp server
 */
class server : public sock {
public:
	server(short port);
	virtual ~server();

	/**
	 * @brief	listen to access
	 */
	int start();

	/**
	 * @brief	stop server
	 */
	void stop();
};

/**
 * @brief	tcp client
 */
class client : public sock, public interface::icomm {
public:
	client();
	virtual ~client();

	/**
	 * @brief	connect to the server
	 */
	int connect(short port);

	/**
	 * @brief	disconnect, if it is connected
	 */
	void disconnect();


	DECLARE_INTERFACE_ICOMM
};


} /* namespace tcp */
} /* namespace net */
} /* namespace cossb */
