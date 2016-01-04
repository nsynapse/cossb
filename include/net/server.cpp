
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
	this->create(port);
}

server::~server()
{
	destroy_task(_event_task);
}

void server::create(const char* port)
{
	if(this->sockfd>0)
		return;

	struct addrinfo _ai;
	struct addrinfo* _ai_ret;

	memset(&_ai, 0, sizeof _ai);

	_ai.ai_family = AF_INET;
	_ai.ai_socktype = SOCK_STREAM;
	_ai.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;

	if(getaddrinfo(nullptr, port ,&_ai, &_ai_ret)!=0)
		throw net::exception(net::excode::SOCKET_GET_ADDRINFO_FAIL);

	if((this->sockfd = socket(_ai_ret->ai_family, _ai_ret->ai_socktype, _ai_ret->ai_protocol))==-1) {
		cossb_log->log(log::loglevel::ERROR, fmt::format("Socket Error : {}",strerror(errno)));
		throw net::exception(net::excode::SOCKET_CREATE_FAIL);
	}
	else {
		if(::bind(this->sockfd, _ai_ret->ai_addr, _ai_ret->ai_addrlen)!=0) {
			cossb_log->log(log::loglevel::ERROR, fmt::format("Socket Error : {}",strerror(errno)));
			close(this->sockfd);
			throw net::exception(net::excode::SOCKET_BIND_FAIL);
		}

		if(!__set_nonblock(this->sockfd))
			cossb_log->log(log::loglevel::ERROR, "non blocking error");
	}

	freeaddrinfo(_ai_ret);
}

int server::start()
{
	if(this->sockfd) {
		::listen(this->sockfd, SOMAXCONN);

		cossb_log->log(log::loglevel::INFO, "Listen socket...");

		//epoll create
		if((epollfd = epoll_create1(EPOLL_CLOEXEC))==-1) {
			cossb_log->log(log::loglevel::ERROR, fmt::format("Epoll Error : {}",strerror(errno)));
			throw net::exception(net::excode::SOCKET_LISTEN_FAIL);
		}

		__add_ev(epollfd, this->sockfd);

		events = (epoll_event*)calloc (max_event, sizeof event);

		if(!_event_task) {
			_event_task = create_task(server::eventtask);
		}
	}
	else
		throw net::exception(net::excode::SOCKET_ALREADY_USE);

	return 0;
}

void server::stop()
{
	if(events)
		free(events);

	if(epollfd)
		close(epollfd);

	destroy_task(_event_task);
}

void server::eventtask()
{
	while(1)
	{
		int result = 0;
		if((result = epoll_wait(epollfd, events, max_event, 0))>0) {

			for(int i=0; i<result; i++) {
				//Error
				if((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || !(events[i].events & EPOLLIN)) {
					cossb_log->log(log::loglevel::ERROR, "Error");
					close (events[i].data.fd);
					continue;
				}

				else if(events[i].data.fd == this->sockfd) {
					while(1) {
						struct sockaddr in_addrs;
						socklen_t in_len = sizeof in_addrs;
						int infd = accept(this->sockfd, &in_addrs, &in_len);
						if(infd==-1) {
							if((errno==EAGAIN) || (errno==EWOULDBLOCK))  //no more new connection
								break;
							break;
						}

						char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
						if(!getnameinfo((struct sockaddr*)&in_addrs, in_len, hbuf, sizeof hbuf, sbuf, sizeof sbuf, NI_NUMERICHOST|NI_NUMERICSERV))
							cossb_log->log(log::loglevel::INFO, fmt::format("Accepted connection on {} : (host={}, port={})", infd, hbuf, sbuf).c_str());

						if(!__set_nonblock(this->sockfd))
							cossb_log->log(log::loglevel::ERROR, "non blocking error");

						__add_ev(epollfd, infd);	//new connection adds to epoll
					}
					continue;
				}
				else {
					while(1) {
						const int size = 2048;
						char* buf = new char[size];
						memset(buf, 0, sizeof(char)*size);

						ssize_t count = ::read(events[i].data.fd, buf, sizeof(char)*size);
						if(count==-1) {
							if(errno != EAGAIN)
								cossb_log->log(log::loglevel::INFO, "EAGAIN");
						}
						else if(count==0) {
							cossb_log->log(log::loglevel::INFO, fmt::format("{} session closed", events[i].data.fd));
							__del_ev(epollfd, events[i].data.fd);
							close (events[i].data.fd);
						}
						else {
							if(_fr)
								(*_fr)(buf, count);
						}

						delete []buf;
						break;
					}

				}
			}
		}

		boost::this_thread::sleep(boost::posix_time::microseconds(0));
	}
}
bool server::__add_ev(int epfd, int fd)
{
	if(fd==-1)
		return false;

	struct epoll_event epev;
	epev.events = EPOLLIN | EPOLLET;
	epev.data.fd = fd;

	if(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &epev)==-1) {
		cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot add event to epoll : {}",strerror(errno)));
		return false;
	}
	return true;
}

bool server::__del_ev(int epfd, int fd)
{
	if(epoll_ctl(epfd, EPOLL_CTL_DEL, fd, nullptr)==-1) {
		cossb_log->log(log::loglevel::ERROR, "Cannot delete event to epoll");
		return false;
	}
	close(fd);
	return true;
}

bool server::__mod_ev(int epfd, int fd, epoll_event* epev)
{
	epev->data.fd = fd;
	if(epoll_ctl(epfd, EPOLL_CTL_MOD, fd, epev)==-1) {
		cossb_log->log(log::loglevel::ERROR, "Cannot modify event to epoll");
		return false;
	}
	return true;
}

bool server::__set_nonblock(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if(flags==-1)
		return false;

	flags |= O_NONBLOCK;

	int s = fcntl(fd, F_SETFL, flags);
	if(s==-1)
		return false;

	return true;
}

void server::set_response_func(func_response func)
{
	if(!_fr)
		_fr = func;
}



} /* namespace tcp */
} /* namespace net */
} /* namespace cossb */
