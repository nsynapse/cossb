

#ifndef _COSSB_COMPONENT_RPI_I2C_HPP_
#define _COSSB_COMPONENT_RPI_I2C_HPP_

#include <interface/icomponent.hpp>
#include <base/task.hpp>


class rpi_i2c : public interface::icomponent  {
public:
	rpi_i2c();
	virtual ~rpi_i2c();

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

private:
	void read();

private:
	unsigned char _write_byte = 0x00;
	cossb::base::task _read_task;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_RPI_I2C_HPP_ */
