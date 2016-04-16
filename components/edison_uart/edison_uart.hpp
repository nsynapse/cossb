

#ifndef _COSSB_COMPONENT_EDISON_UART_HPP_
#define _COSSB_COMPONENT_EDISON_UART_HPP_

#include <interface/icomponent.hpp>
#include <base/task.hpp>


namespace mraa { class Uart; }

class edison_uart : public interface::icomponent  {
public:
	edison_uart();
	virtual ~edison_uart();

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
	void read();

private:
	mraa::Uart* _uart = nullptr;

	cossb::base::task _read_task;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_EDISON_UART_HPP_ */
