

#ifndef _COSSB_COMPONENT_NANOPI_HPP_
#define _COSSB_COMPONENT_NANOPI_HPP_

#include <interface/icomponent.hpp>
#include <base/task.hpp>
#include <map>

using namespace std;


class nanopi : public interface::icomponent  {
public:
	nanopi();
	virtual ~nanopi();

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
	map<int, bool> _gpio_port_map; //true output, false input
	cossb::base::task _gpio_task;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_NANOPI_HPP_ */
