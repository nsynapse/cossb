/**
 * @file		instance.hpp
 * @brief		COSSB Instance
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 7. 27
 * @details	COSSB Instance
 */

#ifndef _COSSB_INSTANCE_HPP_
#define _COSSB_INSTANCE_HPP_

#include <base/manifest.hpp>

namespace cossb {
namespace core {

#ifndef _cplusplus
extern "C" {
#endif

/**
 * @brief create COSSB core instances
 */
extern bool init(const char* manifest_file, bool setup=true);

/**
 * @brief destroy COSSB core instances
 */
extern void destroy();


/**
 * @brief	start COSSB
 */
extern bool start();

/**
 * @brief	stop COSSB
 */
extern bool stop();


#ifndef _cplusplus
}
#endif

} /* namespace core */
} /* namespace cossb */

#endif /* _COSSB_INSTANCE_HPP_ */
