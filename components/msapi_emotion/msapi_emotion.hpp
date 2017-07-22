

#ifndef _COSSB_COMPONENT_MSAPI_EMOTION_HPP_
#define _COSSB_COMPONENT_MSAPI_EMOTION_HPP_

#include <interface/icomponent.hpp>
#include <map>

using namespace std;

class msapi_emotion : public interface::icomponent {
public:
	msapi_emotion();
	virtual ~msapi_emotion();

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

#endif /* _COSSB_COMPONENT_MSAPI_EMOTION_HPP_ */
