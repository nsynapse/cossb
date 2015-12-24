/**
 * @file		errorcode.cpp
 * @brief		Error code definitions
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	component error code definitions
 */

#include "errorcode.hpp"

namespace cossb {
namespace error {

const char* get_error_str(errorcode& e)
{
	switch(e)
	{
	case errorcode::NO_ERROR: 		return		"No Error"; break;
	case errorcode::NULL_PTR: 		return		"Cannot access the memory address"; break;
	case errorcode::UNPACK_FAIL: 	return		"Failed message unpacking"; break;
	case errorcode::SETUP_FAIL:		return		"Failed setup"; break;
	case errorcode::REGIST_FAIL:	return		"Failed registration"; break;
	case errorcode::NOARG:			return		"No Argument";	break;
	default:
		return "Invalid ErrorCode"; break;
	}
}

} /* namespace error */
} /* namespace cossb */
