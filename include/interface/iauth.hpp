/**
 * @file		iauth.hpp
 * @brief		authentication interface
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 7. 29
 * @details	authentication interface class
 */

#ifndef _COSSB_INTERFACE_IAUTH_HPP_
#define _COSSB_INTERFACE_IAUTH_HPP_

namespace cossb {
namespace auth {

typedef struct {
	char code[32] = {0x00, };
} authcode;

enum class authResponse : int {
	NOT_ACCESSIBLE = -1,	// Cannot access Auth system
	NOT_PERMIT = 1,		// Auth Fail
	SUCCESS = 10, 		// Auth Success
};

}
namespace interface {

class iauth {
public:
	virtual ~iauth() { }

	virtual bool authenticate(auth::authcode code, unsigned int len) = 0;
};

} /* namespace interface */
} /* namespace cossb */



#endif /* _COSSB_INTERFACE_IAUTH_HPP_ */
