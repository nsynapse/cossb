/*
 * @brief	camera capture component
 */

#ifndef _COSSB_COMPONENT_CAMCAPTURE_HPP_
#define _COSSB_COMPONENT_CAMCAPTURE_HPP_

#include <interface/icomponent.hpp>
#include <map>
#include <opencv2/videoio.hpp>

using namespace std;

class camcapture : public interface::icomponent {
public:
	camcapture();
	virtual ~camcapture();

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
	cv::Mat& capture();

private:
	cv::VideoCapture* _camera = nullptr;
	int _camera_id = 0;
	bool _show = false;
	unsigned int _resolution_width = 640;
	unsigned int _resolution_height = 480;


};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_CAMCAPTURE_HPP_ */
