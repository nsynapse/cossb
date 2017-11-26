
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
	_gpio_trigger_port = get_profile()->get(profile::section::property, "gpio_trigger").asInt(-1);

	_emotion_gpio[5] = 0x00;
	_emotion_gpio[6] = 0x00;
	_emotion_gpio[13] = 0x00;

	_emotion["anger"] = 0.0;
	_emotion["contempt"] = 0.0;
	_emotion["disgust"] = 0.0;
	_emotion["fear"] = 0.0;
	_emotion["happiness"] = 0.0;
	_emotion["neutral"] = 0.0;
	_emotion["sadness"] = 0.0;
	_emotion["surprise"] = 0.0;

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

		if(!msg->get_frame()->topic.compare("service/msapi/emotion")){
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
	case cossb::base::msg_type::EVENT:  break;
	}
}

void app_timbo::encode(map<string, double>& emotion)
{
	if(emotion.empty())
		return;

	//choose max probability
	double max_value = 0.0;
	string max_emotion = "";
	for(auto const& element:emotion){
		if(element.second>max_value){
			max_value = element.second;
			max_emotion = element.first;
		}
	}

	//emotion code
	if(!max_emotion.compare("anger")) 			{ _emotion_gpio[5]=0x00; _emotion_gpio[6]=0x00; _emotion_gpio[13]=0x01; }
	else if(!max_emotion.compare("contempt")) 	{ _emotion_gpio[5]=0x00; _emotion_gpio[6]=0x01; _emotion_gpio[13]=0x00; }
	else if(!max_emotion.compare("disgust")) 	{ _emotion_gpio[5]=0x00; _emotion_gpio[6]=0x01; _emotion_gpio[13]=0x01; }
	else if(!max_emotion.compare("fear")) 		{ _emotion_gpio[5]=0x01; _emotion_gpio[6]=0x00; _emotion_gpio[13]=0x00; }
	else if(!max_emotion.compare("happiness")) 	{ _emotion_gpio[5]=0x01; _emotion_gpio[6]=0x00; _emotion_gpio[13]=0x01; }
	else if(!max_emotion.compare("sadness")) 	{ _emotion_gpio[5]=0x01; _emotion_gpio[6]=0x01; _emotion_gpio[13]=0x00; }
	else if(!max_emotion.compare("surprise")) 	{ _emotion_gpio[5]=0x01; _emotion_gpio[6]=0x01; _emotion_gpio[13]=0x01; }
	else 										{ _emotion_gpio[5]=0x00; _emotion_gpio[6]=0x00; _emotion_gpio[13]=0x00; }
}


