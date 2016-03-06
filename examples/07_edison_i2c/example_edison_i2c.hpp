/**
 * @file		example_edison_i2c.hpp
 * @brief		I2C write example for edison
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2016. 2. 2
 * @details	data write to edison i2c port
 */

#ifndef _COSSB_EXAMPLE_EDISONI2C_HPP_
#define _COSSB_EXAMPLE_EDISONI2C_HPP_

#include <base/interface.hpp>

using namespace cossb;

class example_edison_i2c : public interface::icomponent {
public:
	example_edison_i2c();
	virtual ~example_edison_i2c();

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
	void write();

private:

	cossb::base::task _task;
};

COMPONENT_EXPORT

#endif /* _COSSB_EXAMPLE_EDISONI2C_HPP_ */
