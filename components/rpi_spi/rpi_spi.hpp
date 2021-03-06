

#ifndef _COSSB_COMPONENT_RPI_SPI_HPP_
#define _COSSB_COMPONENT_RPI_SPI_HPP_

#include <interface/icomponent.hpp>
#include <base/task.hpp>


class rpi_spi : public interface::icomponent  {
public:
	rpi_spi();
	virtual ~rpi_spi();

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
	cossb::base::task _read_task;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_RPI_SPI_HPP_ */
