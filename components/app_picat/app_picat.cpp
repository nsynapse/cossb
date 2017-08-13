
#include "app_picat.hpp"
#include <cossb.hpp>
#include <string>

using namespace std;

USE_COMPONENT_INTERFACE(app_picat)

app_picat::app_picat()
:cossb::interface::icomponent(COMPONENT(app_picat)){

}

app_picat::~app_picat() {

}

bool app_picat::setup()
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

bool app_picat::run()
{
	return false;
}

bool app_picat::stop()
{
	return true;
}

void app_picat::subscribe(cossb::message* const msg)
{

	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST: break;
	case cossb::base::msg_type::DATA: {

		//topic service/rpi_gpio/read
		if(!msg->get_frame()->topic.compare("service/rpi_gpio/read")) {
			//* gpio read subscribe
			try {
				map<int, unsigned char> gpio_data = boost::any_cast<map<int, unsigned char>>(*msg->get_data()); //{key, value} pair

				//if find gpio input signal
				if(gpio_data.find(_gpio_trigger_port)!=gpio_data.end()){
					unsigned char read = gpio_data[_gpio_trigger_port];

					//rising edge
					if(_prev_read==0x00 && read !=0x00){

						//message publish emotion data
						cossb::message msg(this, cossb::base::msg_type::DATA);
						msg.pack(_emotion_gpio);
						cossb_broker->publish("picat_gpio_write", msg);
						cossb_log->log(log::loglevel::INFO, fmt::format("Published gpio write data {}, {}, {}", (int)_emotion_gpio[5], (int)_emotion_gpio[6], (int)_emotion_gpio[13]));
					}
					//falling edge
					else if(_prev_read!=0x00 && read==0x00){
						_emotion_gpio[5] = 0x00;
						_emotion_gpio[6] = 0x00;
						_emotion_gpio[13] = 0x01;

						cossb::message msg(this, cossb::base::msg_type::DATA);
						msg.pack(_emotion_gpio);
						cossb_broker->publish("picat_gpio_write", msg);
						cossb_log->log(log::loglevel::INFO, fmt::format("Published gpio write {}, {}, {}", (int)_emotion_gpio[5], (int)_emotion_gpio[6], (int)_emotion_gpio[13]));
					}

					_prev_read = read;
				}
			}
			catch(const boost::bad_any_cast&){
				cossb_log->log(log::loglevel::ERROR, "Invalid type casting, should be map<int, unsigned char> type.");
			}
		}

		//subscribe emotion data
		else if(!msg->get_frame()->topic.compare("service/msapi/emotion")){
			try {
				map<string, double> emo = boost::any_cast<map<string, double>>(*msg->get_data()); //{key, value} pair
				encode(emo);
			}
			catch(const boost::bad_any_cast&){
			}
		}
	} break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::EVENT:  break;
	}
}

void app_picat::encode(map<string, double>& emotion)
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


