/*
 * irunnable.hpp
 *
 *  Created on: 2015. 8. 24.
 *      Author: hwang-linux
 */

#ifndef INCLUDE_INTERFACE_IRUNNABLE_HPP_
#define INCLUDE_INTERFACE_IRUNNABLE_HPP_


namespace cossb {
namespace interface {

class irunnable {
public:
	virtual ~irunnable() { };

	/**
	 * @brief	run(start) interface
	 */
	virtual void* run() = 0;

	/**
	 * @brief	stop interface
	 */
	virtual void* stop() = 0;

};

} /* namespace interface */
} /* namespace cossb */



#endif /* INCLUDE_INTERFACE_IRUNNABLE_HPP_ */
