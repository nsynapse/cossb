

#ifndef _COSSB_COMPONENT_EDISON_UART_HPP_
#define _COSSB_COMPONENT_EDISON_UART_HPP_

#include <interface/icomponent.hpp>


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
	mraa::Uart* _uart = nullptr;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_EDISON_UART_HPP_ */
