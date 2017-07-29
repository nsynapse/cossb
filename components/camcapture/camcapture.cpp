
#include "camcapture.hpp"
#include <cossb.hpp>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

USE_COMPONENT_INTERFACE(camcapture)

camcapture::camcapture()
:cossb::interface::icomponent(COMPONENT(camcapture)){
	_camera = new cv::VideoCapture(0);
	_camera->set(cv::CAP_PROP_FRAME_WIDTH, 640);
	_camera->set(cv::CAP_PROP_FRAME_HEIGHT, 480);
}

camcapture::~camcapture() {
	if(_camera->isOpened())
		_camera->release();
}

bool camcapture::setup()
{
	return true;
}

bool camcapture::run()
{
	cossb::message<cv::Mat> msg(this);
	//cossb_broker->publish("service/camera/capture", msg);
	return true;
}

bool camcapture::stop()
{
	return true;
}

void camcapture::request(cossb::message* const msg)
{

}

cv::Mat& camcapture::capture()
{
	if(_camera->isOpened())
		(*_camera) >> _colorImage;
	else
		_colorImage.release();

	return _colorImage;
}

