
#include "tcp.hpp"
#include <net/exception.hpp>
#include <base/log.hpp>

namespace cossb {
namespace net {
namespace tcp {

const int max_event = 256;

server::server(const char* port)
:sock(net::netType::SERVER)
{
	create(port);
}

server::~server()
{
	destroy_task(_event_task);
}

void server::create(const char* port)
{
	struct addrinfo _ai;
	struct addrinfo* _ai_ret;

	memset(&_ai, 0, sizeof _ai);

	_ai.ai_family = AF_INET;
	_ai.ai_socktype = SOCK_STREAM;
	_ai.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;

	if(getaddrinfo(nullptr, port ,&_ai, &_ai_ret)!=0) {
		throw net::exception(net::excode::SOCKET_GET_ADDRINFO_FAIL);
	}

	if((this->sockfd = socket(_ai_ret->ai_family, _ai_ret->ai_socktype, _ai_ret->ai_protocol))==-1) {
		throw net::exception(net::excode::SOCKET_CREATE_FAIL);
	}
	else {
		if(::bind(this->sockfd, _ai_ret->ai_addr, _ai_ret->ai_addrlen)!=0) {
			close(this->sockfd);
			throw net::exception(net::excode::SOCKET_BIND_FAIL);
		}

		fcntl(this->sockfd, F_SETFL, fcntl(this->sockfd, F_GETFL|O_NONBLOCK));	//change to non-blocking mode
	}

	freeaddrinfo(_ai_ret);
}

int server::start()
{
	if(this->sockfd) {
		::listen(this->sockfd, SOMAXCONN);

		cossb_log->log(log::loglevel::INFO, "Listen socket...");

		//epoll create
		if((epollfd = epoll_create1(0))==-1)
			throw net::exception(net::excode::SOCKET_LISTEN_FAIL);

		//add
		event.data.fd = this->sockfd;
		event.events = EPOLLIN | EPOLLET;
		if(epoll_ctl(epollfd, EPOLL_CTL_ADD, this->sockfd, &event)==-1)
			throw net::exception(net::excode::SOCKET_LISTEN_FAIL);

		events = (epoll_event*)calloc (max_event, sizeof event);

		if(!_event_task)
			_event_task = create_task(server::eventtask);
	}
	return 0;
}

void server::stop()
{
	if(epollfd)
		close(epollfd);

	destroy_task(_event_task);
	cossb_log->log(log::loglevel::INFO, "event task destroy");
}

void server::eventtask()
{
	while(1)
	{
		/*int npoll = 0;
		if((npoll = epoll_wait(epollfd, events, max_event, -1))!=-1) {
			for(int i=0;i<npoll;i++) {
				if(events[i].events & EPOLLIN) {
					if(events[i].data.fd == this->sockfd) {
						struct sockaddr_storage saddr_c;
						while(1) {
							socklen_t len_saddr = sizeof(saddr_c);
							int fd = accept(this->sockfd, (struct sockaddr*)&saddr_c, &len_saddr);
							if(fd==-1) {

							}
						}
					}
				}
			}
		}*/
		cossb_log->log(log::loglevel::INFO, "event task");
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	}
}

} /* namespace tcp */
} /* namespace net */
} /* namespace cossb */
