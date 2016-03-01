/**
 * @file		example_messageout.hpp
 * @brief		messageout Component Example
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2016. 2. 2
 * @details	message send to topic
 */

#ifndef _COSSB_EXAMPLE_MESSAGEOUT_HPP_
#define _COSSB_EXAMPLE_MESSAGEOUT_HPP_

#include <base/interface.hpp>

using namespace cossb;

class example_messageout : public interface::icomponent {
public:
	example_messageout();
	virtual ~example_messageout();

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

	void do_task();

private:

	cossb::base::task _task;
};

COMPONENT_EXPORT

#endif /* _COSSB_EXAMPLE_MESSAGEOUT_HPP_ */
