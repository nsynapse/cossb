/**
 * @file		errorcode.hpp
 * @brief		Error code definitions
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	component error code definitions
 */



#ifndef _COSSB_ERRORCODE_HPP_
#define _COSSB_ERRORCODE_HPP_

namespace cossb {
namespace error {

enum class errorcode : unsigned long {
	NO_ERROR = 1,
	NULL_PTR,

	UNPACK_FAIL,
	SETUP_FAIL,
	REGIST_FAIL,

	NOARG,
};

#ifndef _cplusplus
extern "C" {
#endif

/**
 * @brief	return error string
 * @details	return error string from argument e
 */
const char* get_error_str(errorcode& e);

#ifndef _cplusplus
}
#endif

} /* namespace error */
} /* namespace cossb */

#endif /* _COSSB_ERRORCODE_HPP_ */
