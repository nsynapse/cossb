/**
 * @file		exception.hpp
 * @brief		COSSB exception
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 23
 * @details	cossb exception header
 */


#ifndef _COSSB_EXCEPTION_HPP_
#define _COSSB_EXCEPTION_HPP_


#include <string>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <base/log.hpp>
#include <util/format.h>

using namespace std;


namespace cossb {
namespace exception {

enum class excode : int {
	DRIVER_NOT_FOUND = 0,
	COMPONENT_LOAD_FAIL,	//driver cannnot be loaded own component
	COMPONENT_UNLOAD_FAIL,
};

class cossb_exception : public std::exception {
public:
	cossb_exception() { }
	cossb_exception(excode code) {
		switch(code)
		{
		case excode::DRIVER_NOT_FOUND: 		set("Driver cannot be found");  break;
		case excode::COMPONENT_LOAD_FAIL: 	set("Component load fail"); break;
		case excode::COMPONENT_UNLOAD_FAIL: set("Component unload fail"); break;
		default:
			set("Unknown Exception");
		}
	}
	~cossb_exception() throw() { }
	virtual const char* what() const throw() { return exception_str.c_str(); }
protected:
	void set(const char* msg) { exception_str = msg; }
private:
	std::string exception_str;
};

} /* namespace exception */
//
//namespace broker {
//enum class excode : int {
//	DRIVER_NOT_FOUND = 0,
//	COMPONENT_LOAD_FAIL = 0,	//driver cannnot be loaded own component
//	COMPONENT_UNLOAD_FAIL,
//};
//
///**
// * @brief	broker exception
// */
//class exception : public cossb::exception::cossb_exception {
//public:
//	exception(broker::excode code) {
//		switch(code)
//		{
//		case excode::DRIVER_NOT_FOUND: set("Driver cannot be found");  break;
//		case excode::COMPONENT_LOAD_FAIL: set("Component load fail"); break;
//		case excode::COMPONENT_UNLOAD_FAIL: set("Component unload fail"); break;
//		default:
//			set("Unknown Exception");
//		}
//	}
//};
//
//} /* namespace broker */


//namespace driver {
//
//enum class excode : int {
//	COMPONENT_LOAD_FAIL = 0,	//driver cannnot be loaded own component
//	COMPONENT_UNLOAD_FAIL,
//};
//
///**
// * @brief	component driver exception
// */
//class exception : public cossb::exception::cossb_exception {
//public:
//	exception(driver::excode code, const char* err_msg = nullptr) {
//		switch(code) {
//		case excode::COMPONENT_LOAD_FAIL: set("Component load fail"); break;
//		case excode::COMPONENT_UNLOAD_FAIL: set("Component unload fail"); break;
//		default: set("Unknown exception");
//		}
//	}
//};
//
//} /* namespace driver */

} /* namespace cossb */


#endif /* _COSSB_EXCEPTION_HPP_ */
