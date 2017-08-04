/*
 * @brief	image viewer
 */

#ifndef _COSSB_COMPONENT_IMAGEVIEWER_HPP_
#define _COSSB_COMPONENT_IMAGEVIEWER_HPP_

#include <interface/icomponent.hpp>
#include <map>

using namespace std;

class imageviewer : public interface::icomponent {
public:
	imageviewer();
	virtual ~imageviewer();

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

};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_IMAGEVIEWER_HPP_ */
