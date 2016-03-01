

#ifndef _COSSB_COMPONENT_EDISON_GPIO_HPP_
#define _COSSB_COMPONENT_EDISON_GPIO_HPP_

#include <interface/icomponent.hpp>
#include <map>

using namespace std;

namespace mraa{ class Gpio; }

class edison_gpio : public interface::icomponent {
public:
	edison_gpio();
	virtual ~edison_gpio();

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
	 * @brief	GPIO Map
	 * @detail	<port number>, <Gpio instance>
	 */
	map<int, mraa::Gpio*> _iomap;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_EDISON_GPIO_HPP_ */
