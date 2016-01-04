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
#include <errno.h>
#include <signal.h>
#include <interface/icomm.hpp>

using namespace std;

namespace cossb {
namespace net {
namespace tcp {

typedef int (*func_response)(const char* data, int len);

/**
 * @brief	tcp server (single threaded)
 */
class server : public sock {
public:
	server(const char* port);
	virtual ~server();

	/**
	 * @brief	start server
	 */
	int start();

	/**
	 * @brief	stop server
	 */
	void stop();

	/**
	 * @brief	response function
	 */
	void set_response_func(func_response func);


protected:
	/**
	 * @brief	create server
	 */
	void create(const char* port);

private:
	bool __add_ev(int epfd, int fd);
	bool __del_ev(int epfd, int fd);
	bool __mod_ev(int epfd, int fd, epoll_event* epev);
	bool __set_nonblock(int fd);

	void eventtask();

protected:
	struct epoll_event event;
	struct epoll_event* events = nullptr;
	int epollfd = -1;

private:
	base::task _event_task;
	func_response _fr = nullptr;
};

/**
 * @brief	tcp client
 */
class client : public sock {
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

};


} /* namespace tcp */
} /* namespace net */
} /* namespace cossb */
