
/**
 * @file		pid.hpp
 * @brief		Processing ID control class
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 1
 * @details	Some services may requires process IDs of applications
 */

#ifndef _COSSB_UTIL_PID_H_
#define _COSSB_UTIL_PID_H_

namespace cossb {
namespace util {

#ifndef _cplusplus
extern "C"
{
#endif


/**
 * @brief	get pid by name
 */
extern int get_pid(const char* processname);

#ifndef _cplusplus
}
#endif


} /*  */
} /* namespace cossb */

#endif /* _COSSB_UTIL_PID_H_ */
