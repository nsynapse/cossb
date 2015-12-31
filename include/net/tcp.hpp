/**
 * @file		tcp.hpp
 * @brief		tcp protocol class
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 10. 3
 * @details		TCP
 */

#include <net/sock.hpp>
#include <base/task.hpp>
#include <interface/icomm.hpp>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <netdb.h>

namespace cossb {
namespace net {
namespace tcp {

/**
 * @brief	tcp server
 */
class server : public sock {
public:
	server(const char* port);
	virtual ~server();

	/**
	 * @brief	listen to access
	 */
	int start();

	/**
	 * @brief	stop server
	 */
	void stop();

private:

	/**
	 * @brief	create socket
	 */
	void create(const char* port);

	void eventtask();

protected:
	struct epoll_event event;
	struct epoll_event* events;
	int epollfd = -1;

private:
	base::task _event_task;
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
