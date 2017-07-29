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
	void request(cossb::message* const msg);

private:
	cv::Mat& capture();

private:
	cv::VideoCapture* _camera = nullptr;
	cv::Mat _colorImage;


};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_CAMCAPTURE_HPP_ */
