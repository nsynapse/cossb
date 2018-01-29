/**
* @file		math.hpp
* @brief
* @author	Byunghun Hwang (bhhwang@dgist.ac.kr)
*/

#ifndef __COMMON_UTIL_MATH__
#define __COMMON_UTIL_MATH__

#define M_PI 3.14159265358979323846

#ifndef DEG2RAD
#define DEG2RAD(x) ((x) * 0.01745329251994329575)
#endif

#ifndef RAD2DEG
#define RAD2DEG(x) ((x) * 57.29577951308232087721)
#endif

#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif

#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef ROUND
#define ROUND(x) ((x) < 0 ? (int)((x) - .5): (int) ((x) + .5))
#endif

#ifndef SIGN
#define SIGN(a) ((a)>0?1:((a)<0?-1:0))
#endif

#ifndef IS_ZERO
#define IS_ZERO(f) (fabs(f) < 1e-12)
#endif

#ifndef IS_EQUAL
#define IS_EQUAL(f, g) (fabs(f - g) < 1e-12)
#endif

#endif
