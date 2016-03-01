

#ifndef _COSSB_COMPONENT_EDISON_I2C_HPP_
#define _COSSB_COMPONENT_EDISON_I2C_HPP_

#include <interface/icomponent.hpp>

class edison_i2c : public interface::icomponent  {
public:
	edison_i2c();
	virtual ~edison_i2c();

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

#endif /* _COSSB_COMPONENT_EDISON_I2C_HPP_ */
