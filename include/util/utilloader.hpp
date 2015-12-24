/**
 * @file		utilloader.cpp
 * @brief		Utility library loader
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 9. 6
 * @details	cossb utility loader class and it derived from iutility class
 */

#ifndef _COSSB_UTIL_LOADER_HPP_
#define _COSSB_UTIL_LOADER_HPP_

#include "../interface/iutility.hpp"

namespace cossb {
namespace util {

class utilloader : public interface::iutility {
public:
	utilloader(const char* target_util);
	virtual ~utilloader();

	/**
	 * @brief	launch interface
	 */
	bool execute(int argc, char* argv[]);

private:
	/**
	 * @brief	load utility load
	 */
	bool load(const char* target_util);

	/**
	 * @brief	unload utility load
	 */
	void unload();


private:
	void* _util_handle = nullptr;
};

} /* namespace util */
} /* namespace cossb */

#endif /* _COSSB_UTIL_LOADER_HPP_ */
