

#ifndef _COSSB_COMPONENT_RPI_I2C_HPP_
#define _COSSB_COMPONENT_RPI_I2C_HPP_

#include <interface/icomponent.hpp>
#include <base/task.hpp>
#include <3rdparty/bcm2835.h>

typedef enum {
    NO_ACTION,
    I2C_BEGIN,
    I2C_END
} i2c_init;

#define MODE_READ 0
#define MODE_WRITE 1


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
	void subscribe(cossb::message* const msg);

private:
	void read();

private:
	unsigned char _write_byte = 0x00;
	base::task _read_task;
	unsigned short _clk_div = BCM2835_I2C_CLOCK_DIVIDER_150;

};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_RPI_I2C_HPP_ */
