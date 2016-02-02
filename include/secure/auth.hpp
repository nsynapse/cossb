
/**
 * @file		auth.hpp
 * @brief		authentication headers
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2016. 1. 11
 * @details	authentication for cossb
 */

#ifndef _COSSB_AUTH_HPP_
#define _COSSB_AUTH_HPP_

#include <base/interface.hpp>
#include <arch/singleton.hpp>

namespace cossb {
namespace secure {

class auth_PB : public arch::singleton<auth_PB>
{
public:
	auth_PB();
	virtual ~auth_PB();


};

} /* namespace secure */
} /* namespace cossb */

#endif /* _COSSB_AUTH_HPP_ */
