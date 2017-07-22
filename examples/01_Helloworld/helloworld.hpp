/**
 * @file		helloworld.hpp
 * @brief		Hello World Component Example
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details		This is simple service component
 */

#ifndef _COSSB_EXAMPLE_HELLOWORLD_HPP_
#define	_COSSB_EXAMPLE_HELLOWORLD_HPP_

#include <base/interface.hpp>

using namespace cossb;

class helloworld : public interface::icomponent {
public:
	helloworld();
	virtual ~helloworld();

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
	void request(cossb::message* const msg);
};

COMPONENT_EXPORT

#endif /* _COSSB_EXAMPLE_HELLOWORD_HPP_ */
