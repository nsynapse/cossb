/**
 * @file		iutility.cpp
 * @brief		utility interface class
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 9. 6
 * @details	utility interface class
 */

#ifndef _COSSB_IUTILITY_HPP_
#define _COSSB_IUTILITY_HPP_

#include <sys/stat.h>


namespace cossb {
namespace interface {

class iutility {
public:
	iutility() { }
	virtual ~iutility() {
	}

	/**
	 * @brief	launch interface function
	 * @details	pass all arguments to launch interface, inherited class should control the arguments
	 */
	virtual bool execute(int argc, char* argv[]) = 0;

protected:

	bool exist(const char* utility) {
		struct stat buf;
		return (stat(utility, &buf)==0);
	}
};


} /* namespace interface */
} /* namespace cossb */

#ifdef __cplusplus
extern "C" {
#endif

bool execute(int argc, char* argv[]);

#ifdef __cplusplus
}
#endif

#define USE_UTILITY_INTERFACE_EXECUTE(classname) extern "C" bool execute(int argc, char* argv[]) { \
	classname* util = new classname();	\
	bool ret = util->execute(argc, argv);	\
	delete util;	\
	return ret; \
}


#endif /* _COSSB_IUTILITY_HPP_ */
