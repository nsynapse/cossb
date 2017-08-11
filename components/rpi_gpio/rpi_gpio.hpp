

#ifndef _COSSB_COMPONENT_RPI_GPIO_HPP_
#define _COSSB_COMPONENT_RPI_GPIO_HPP_

#include <interface/icomponent.hpp>
#include <base/task.hpp>
#include <map>

using namespace std;


class rpi_gpio : public interface::icomponent  {
public:
	rpi_gpio();
	virtual ~rpi_gpio();

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

	map<int, bool> _portmap; //{port, set(1=output, 0=input)}
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_RPI_GPIO_HPP_ */
