/**
 * @file		example_cat_monitoring.hpp
 * @brief		CAT component for sensor monitoring
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2016. 4. 20
 * @details		CAT component
 */

#ifndef _COSSB_EXAMPLE_CAT_MONITORING_HPP_
#define _COSSB_EXAMPLE_CAT_MONITORING_HPP_

#include <base/interface.hpp>
#include <string>

using namespace std;
using namespace cossb;

class example_cat_monitoring : public interface::icomponent {
public:
	example_cat_monitoring();
	virtual ~example_cat_monitoring();

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
	void write();

private:
	cossb::base::task _task;
};

COMPONENT_EXPORT

#endif /* _COSSB_EXAMPLE_CAT_MONITORING_HPP_ */
