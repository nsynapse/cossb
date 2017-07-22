

#ifndef _COSSB_COMPONENT_CV_CAPTURE_HPP_
#define _COSSB_COMPONENT_CV_CAPTURE_HPP_

#include <interface/icomponent.hpp>
#include <map>

using namespace std;

class cv_capture : public interface::icomponent {
public:
	cv_capture();
	virtual ~cv_capture();

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
	void request(cossb::message* const msg);

private:

};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_EDISON_GPIO_HPP_ */
