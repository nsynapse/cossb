/*
 * compcontroller.hpp
 *
 *  Created on: 2016. 8. 15.
 *      Author: hwang
 */

#ifndef _COSSB_COMPONENT_COMPCONTROLLER_HPP_
#define _COSSB_COMPONENT_COMPCONTROLLER_HPP_

#include <base/interface.hpp>

using namespace cossb;

class compcontroller : public interface::icomponent{
public:
	compcontroller();
	virtual ~compcontroller();

	/**
	 * @brief	setup interface function
	 */
	bool setup();

	/**
	 * @brief	run interface function
	 */
	bool run();

	/**
	 * @brief	stop interface function
	 */
	bool stop();

	/**
	 * @brief	request interface function
	 */
	void request(cossb::base::message* const msg);
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_COMPCONTROLLER_HPP_ */
