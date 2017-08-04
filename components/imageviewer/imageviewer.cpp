
#include "imageviewer.hpp"
#include <cossb.hpp>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

USE_COMPONENT_INTERFACE(imageviewer)

imageviewer::imageviewer()
:cossb::interface::icomponent(COMPONENT(imageviewer)){

}

imageviewer::~imageviewer() {

}

bool imageviewer::setup()
{
	cv::namedWindow("viewer");
	return true;
}

bool imageviewer::run()
{
	return true;
}

bool imageviewer::stop()
{
	cv::destroyWindow("viewer");

	return true;
}

void imageviewer::subscribe(cossb::message* const msg)
{
	switch(msg->get_frame()->type) {
		case cossb::base::msg_type::REQUEST: break;
		case cossb::base::msg_type::DATA: {

			//subscribe emotion data
			try {
			cv::Mat image = boost::any_cast<cv::Mat>(*msg->get_data());
			if(!image.empty()){
				cv::imshow("viewer", image);
				cv::waitKey(10);
			}

			cossb_log->log(log::loglevel::INFO, "Subscribed Image");
			}
			catch(const boost::bad_any_cast&){
				cossb_log->log(log::loglevel::ERROR, "Invalid type casting");
			}
		} break;
		case cossb::base::msg_type::RESPONSE: break;
		case cossb::base::msg_type::EVENT:  break;
		}
}

