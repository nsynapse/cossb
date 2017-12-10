/*
 * nanopi_timbo.hpp
 *
 *  Created on: Dec 10, 2017
 *      Author: hwangvm
 */

#ifndef COMPONENTS_NANOPI_TIMBO_NANOPI_TIMBO_HPP_
#define COMPONENTS_NANOPI_TIMBO_NANOPI_TIMBO_HPP_





#endif /* COMPONENTS_NANOPI_TIMBO_NANOPI_TIMBO_HPP_ */


#ifndef _COSSB_COMPONENT_NANOPI_HPP_
#define _COSSB_COMPONENT_NANOPI_HPP_

#include <interface/icomponent.hpp>
#include <base/task.hpp>
#include <map>
#include <string>

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

	//send trajectory

private:
	//map<int, bool> _gpio_port_map; //true output, false input
	//map<int, int> _gpio_port_read;
	cossb::base::task _gpio_task;
};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_NANOPI_HPP_ */
