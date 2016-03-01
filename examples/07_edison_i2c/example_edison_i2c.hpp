/**
 * @file		example_messageprint.hpp
 * @brief		messageprint Component Example
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2016. 2. 2
 * @details	message send to topic
 */

#ifndef _COSSB_EXAMPLE_MESSAGEPRINT_HPP_
#define _COSSB_EXAMPLE_MESSAGEPRINT_HPP_

#include <base/interface.hpp>

using namespace cossb;

class example_messageprint : public interface::icomponent {
public:
	example_messageprint();
	virtual ~example_messageprint();

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
	 * @brief	print message to console
	 */
	void printout(const char* msg);

private:

	cossb::base::task _task;
};

COMPONENT_EXPORT

#endif /* _COSSB_EXAMPLE_MESSAGEPRINT_HPP_ */
