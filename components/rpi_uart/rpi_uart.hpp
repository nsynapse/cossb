

#ifndef _COSSB_COMPONENT_RPI_UART_HPP_
#define _COSSB_COMPONENT_RPI_UART_HPP_

#include <interface/icomponent.hpp>
#include <base/task.hpp>
#include "libserial.hpp"

class rpi_uart : public interface::icomponent  {
public:
	rpi_uart();
	virtual ~rpi_uart();

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
	libserial* _uart = nullptr;
	string _port;
	cossb::base::task _read_task;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_RPI_UART_HPP_ */
