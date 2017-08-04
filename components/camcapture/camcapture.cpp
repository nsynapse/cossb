
#include "camcapture.hpp"
#include <cossb.hpp>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

USE_COMPONENT_INTERFACE(camcapture)

camcapture::camcapture()
:cossb::interface::icomponent(COMPONENT(camcapture)){

}

camcapture::~camcapture() {

}

bool camcapture::setup()
{
	_camera_id = get_profile()->get(profile::section::property, "camid").asInt(0);
	_resolution_width = get_profile()->get(profile::section::property, "resolution_width").asUInt(640);
	_resolution_height = get_profile()->get(profile::section::property, "resolution_height").asUInt(480);
	_show = get_profile()->get(profile::section::property, "show").asBool(false);


	cossb_log->log(log::loglevel::INFO, fmt::format("Camera #{} : {}x{} resolution", _camera_id, _resolution_width, _resolution_height));

	_camera = new cv::VideoCapture(_camera_id);
	if(_camera->isOpened()){
		_camera->set(cv::CAP_PROP_FRAME_WIDTH, 640);
		_camera->set(cv::CAP_PROP_FRAME_HEIGHT, 480);

		if(_show)
			cv::namedWindow("Image");

		return true;
	}
	cossb_log->log(log::loglevel::ERROR, "Camera Open Failed");
	return false;
}

bool camcapture::run()
{
	if(_camera->isOpened()){
		(*_camera) >> _colorImage;

		if(!_colorImage.empty() && _show){
			cv::imshow("Image", _colorImage);
			cv::waitKey(1);
		}

//		cossb::message _msg(this, base::msg_type::DATA);
//		_msg.set(_colorImage.clone());
//		cossb_broker->publish("camera_capture", _msg);


		//cossb_log->log(log::loglevel::INFO, "Camera Capture and publish data");
	}
	else
		_colorImage.release();


	return true;
}

bool camcapture::stop()
{
	if(_show)
		cv::destroyWindow("Image");

	if(_camera->isOpened())
		_camera->release();

	return true;
}

void camcapture::request(cossb::message* const msg)
{

}

