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
class cossb_exception : public std::exception {
public:
	cossb_exception() { }
	~cossb_exception() throw() { }
	virtual const char* what() const throw() {
		return exception_str.c_str();
	}
protected:
	void set(const char* msg) { exception_str = msg; }
private:
	std::string exception_str;
};
} /* namespace exception */

namespace broker {
enum class excode : int {
	DRIVER_NOT_FOUND=0,
};

/**
 * @brief	broker exception
 */
class exception : public cossb::exception::cossb_exception {
public:
	exception(broker::excode code) {
		switch(code)
		{
		case	excode::DRIVER_NOT_FOUND: set("Driver cannot be found");  break;
		default:
			set("Unknown Exception");
		}
	}
};

} /* namespace broker */


namespace driver {

enum class excode : int {
	COMPONENT_LOAD_FAIL = 0,	//driver cannnot be loaded own component
	COMPONENT_UNLOAD_FAIL,
	COMPONENT_OPEN_ERROR,
};

/**
 * @brief	component driver exception
 */
class exception : public cossb::exception::cossb_exception {
public:
	exception(driver::excode code, const char* err_msg = nullptr) {
		switch(code) {
		case excode::COMPONENT_LOAD_FAIL: set("Component load fail"); break;
		case excode::COMPONENT_UNLOAD_FAIL: set("Component unload fail"); break;
		case excode::COMPONENT_OPEN_ERROR: err_msg?set(err_msg):set("No error message"); break;
		default: set("Unknown exception");
		}
	}
};

} /* namespace driver */

namespace net {
enum class excode : int {
	NET_OPEN_FAIL = 0,
	NET_WRITE_FAIL,
	NET_READ_FAIL,
	SOCKET_CREATE_FAIL,
	SOCKET_BIND_FAIL,
	SOCKET_SET_REUSE_FAIL,
	SOCKET_SET_ADDMEMBERSHIP_FAIL,
	SOCKET_SET_TIMEOUT_FAIL,
};
/**
 * @brief	network exception
 */
class exception : public cossb::exception::cossb_exception {
public:
	exception(net::excode code, const char* err_msg = nullptr) {
		switch(code) {
		case excode::NET_OPEN_FAIL: set("Network open fail"); break;
		case excode::NET_WRITE_FAIL: set("Network write fail"); break;
		case excode::NET_READ_FAIL: set("Network read fail"); break;
		case excode::SOCKET_CREATE_FAIL: set("Network socket create fail"); break;
		case excode::SOCKET_BIND_FAIL: set("Network bind fail"); break;
		case excode::SOCKET_SET_REUSE_FAIL: set("Network reuse setting fail"); break;
		case excode::SOCKET_SET_ADDMEMBERSHIP_FAIL: set("Network add membership fail"); break;
		case excode::SOCKET_SET_TIMEOUT_FAIL: set("Network timeout setting fail"); break;
		default: set(fmt::format("Unknown exception({})", (int)code).c_str());
		}
	}
};

} /* namespace net */

} /* namespace cossb */


#endif /* _COSSB_EXCEPTION_HPP_ */
