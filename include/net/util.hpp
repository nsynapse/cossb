

#ifndef _COSSB_NET_UTIL_
#define _COSSB_NET_UTIL_

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <net/if.h>

namespace cossb {
namespace net {

typedef struct _macAddress {
	unsigned char address[6];
} macAddress;

	inline macAddress getMacAddress(const char* ifname){
		struct ifreq s;
		macAddress _mac;
		int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
		strcpy(s.ifr_name, ifname);
		if(!ioctl(fd, SIOCGIFHWADDR, &s)){
			for(int i=0;i<6;i++)
				_mac.address[i] = (unsigned char)s.ifr_hwaddr.sa_data[i];
		}
		return _mac;
	}

} /* namespace net */
} /* namespace cossb */


#endif /* _COSSB_NET_UTIL_ */
