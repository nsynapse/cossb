/**
 * @file		example_edison_gpio.hpp
 * @brief		Edison GPIO examples
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2016. 2. 2
 * @details	GPIO component for Edison
 */

#ifndef _COSSB_EXAMPLE_EDISON_GPIO_HPP_
#define _COSSB_EXAMPLE_EDISON_GPIO_HPP_

#include <base/interface.hpp>

using namespace cossb;

class example_edison_gpio : public interface::icomponent {
public:
	example_edison_gpio();
	virtual ~example_edison_gpio();

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

private:

	/**
	 * @brief	print message to console
	 */
	void printout(const char* msg);

private:

	cossb::base::task _task;
};

COMPONENT_EXPORT

#endif /* _COSSB_EXAMPLE_EDISON_GPIO_HPP_ */
