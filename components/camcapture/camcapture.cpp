
#include "camcapture.hpp"
#include <cossb.hpp>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

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

		return true;
	}
	cossb_log->log(log::loglevel::ERROR, "Camera Open Failed");
	return false;
}

bool camcapture::run()
{
	if(_camera->isOpened()){
		cv::Mat _colorImage;
		(*_camera) >> _colorImage;

		if(!_colorImage.empty()){
			cossb::message _msg(this, base::msg_type::DATA);
			_msg.set(_colorImage.clone());
			cossb_broker->publish("camera_capture", _msg);

			cossb_log->log(log::loglevel::INFO, "Published captured image");
		}
		return true;
	}
	return false;
}

bool camcapture::stop()
{
	if(_camera->isOpened())
		_camera->release();

	return true;
}

void camcapture::subscribe(cossb::message* const msg)
{

}

