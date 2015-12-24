/**
 * @file		version.hpp
 * @brief		Software Version Header
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 9
 * @details
 */

#ifndef _COSSB_VERSION_HPP_
#define _COSSB_VERSION_HPP_

#define COSSB_NAME	"COSSB "

#ifdef __MAJOR__
#define COSSB_VERSION_MAJOR	__MAJOR__
#else
#define COSSB_VERSION_MAJOR x
#endif

#ifdef __MINOR__
#define COSSB_VERSION_MINOR	__MINOR__
#else
#define COSSB_VERSION_MINOR	x
#endif

#ifdef __REV__
#define COSSB_VERSION_REV	__REV__
#else
#define COSSB_VERSION_REV	x
#endif

#define VERSION_STR(x) #x
#define COSSB_VERSION_SET(major, minor, rev)	VERSION_STR(major) "." VERSION_STR(minor) "." VERSION_STR(rev)
#define COSSB_VERSION	COSSB_VERSION_SET(COSSB_VERSION_MAJOR, COSSB_VERSION_MINOR, COSSB_VERSION_REV)


#endif /* _COSSB_VERSION_HPP_ */


