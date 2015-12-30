#include "tcp.hpp"

namespace cossb {
namespace net {
namespace tcp {

client::client()
:sock(net::netType::CLIENT)
{

}

client::~client()
{

}

int client::connect(short port)
{
	return 0;
}

void client::disconnect()
{

}

int client::read() const
{
	return 0;
}

int client::write(const char* data, int len)
{
	return 0;
}




} /* namespace tcp */
} /* namespace net */
} /* namespace cossb */
