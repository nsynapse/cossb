
#include "app_timbo.hpp"
#include <cossb.hpp>
#include <string>

using namespace std;

USE_COMPONENT_INTERFACE(app_timbo)

app_timbo::app_timbo()
:cossb::interface::icomponent(COMPONENT(app_timbo)){

}

app_timbo::~app_timbo() {

}

bool app_timbo::setup()
{


	return true;
}

bool app_timbo::run()
{
	return false;
}

bool app_timbo::stop()
{
	return true;
}

void app_timbo::subscribe(cossb::message* const msg)
{

	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST: break;
	case cossb::base::msg_type::DATA: {

		//
		if(!msg->get_frame()->topic.compare("service/serial/read")){
			try {
				map<string, double> emo = boost::any_cast<map<string, double>>(*msg->get_data()); //{key, value} pair
				encode(emo);

				cossb::message msg(this, cossb::base::msg_type::DATA);
				msg.pack(_emotion_gpio);
				cossb_broker->publish("picat_gpio_write", msg);
				cossb_log->log(log::loglevel::INFO, fmt::format("Published gpio write {}, {}, {}", (int)_emotion_gpio[5], (int)_emotion_gpio[6], (int)_emotion_gpio[13]));
			}
			catch(const boost::bad_any_cast&){
				cossb_log->log(log::loglevel::ERROR, "Invalid type casting, should be map<string, double> type.");
			}
		}
	} break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::EVENT: break;
	}
}



