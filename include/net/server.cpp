
#include "tcp.hpp"
#include <net/exception.hpp>

namespace cossb {
namespace net {
namespace tcp {

server::server(short port)
:sock(net::netType::SERVER)
{
	if((this->sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP))==-1)
		throw net::exception(net::excode::SOCKET_CREATE_FAIL);
	else {
		memset(&this->address, 0, sizeof(this->address));
		this->address.sin_family = AF_INET;
		this->address.sin_addr.s_addr = INADDR_ANY;
		this->address.sin_port = htons(port);

		unsigned int reuse = 1;
		if(setsockopt(this->sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse))<0)
			throw net::exception(net::excode::SOCKET_SET_REUSE_FAIL);

		if(::bind(this->sockfd, (struct sockaddr*)&this->address, sizeof(this->address))<0)
			throw net::exception(net::excode::SOCKET_BIND_FAIL);

		if(port==0) {
			socklen_t len = sizeof(this->address);
			getsockname(this->sockfd, (struct sockaddr*)&this->address, &len);
		}
	}
}
server::~server()
{

}

int server::start()
{
	if(this->sockfd) {
		::listen(this->sockfd, 5);
	}
	return 0;
}

void server::stop()
{

}

} /* namespace tcp */
} /* namespace net */
} /* namespace cossb */
