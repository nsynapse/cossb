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


} /* namespace tcp */
} /* namespace net */
} /* namespace cossb */
