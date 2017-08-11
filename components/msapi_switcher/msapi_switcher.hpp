

#ifndef _COSSB_COMPONENT_MSAPI_SWITCHER_HPP_
#define _COSSB_COMPONENT_MSAPI_SWITCHER_HPP_

#include <interface/icomponent.hpp>
#include <base/task.hpp>
#include <map>

using namespace std;


class msapi_switcher : public interface::icomponent  {
public:
	msapi_switcher();
	virtual ~msapi_switcher();

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
	int _gpio = -1;

};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_MSAPI_SWITCHER_HPP_ */
