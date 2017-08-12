
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
	_gpio_trigger = get_profile()->get(profile::section::property, "gpio").asInt(-1);

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
				map<int, unsigned char> gpio_data = boost::any_cast<map<int, unsigned char>>(*msg); //{key, value} pair

				if(gpio_data.find(_gpio_trigger)!=gpio_data.end()){
					unsigned char read = gpio_data[_gpio_trigger];
					if(_prev_read==0x00 && read!=0x00){

						//get emotion code
						unsigned char code = encode(_emotion);

						//message publish emotion data
						cossb::message msg(this, cossb::base::msg_type::DATA);
						msg.pack(code);
						cossb_broker->publish("picat_gpio_write", msg);
						cossb_log->log(log::loglevel::INFO, fmt::format("Published Emotion code : {}", (int)code));
					}
					_prev_read = read;
				}
			}
			catch(const boost::bad_any_cast&){
				//cossb_log->log(log::loglevel::ERROR, "Invalid type casting, should be map<int, unsigned char> type.");
			}
		}

		//topic
		else if(!msg->get_frame()->topic.compare("service/msapi/emotion")){
			try {
				map<string, double> emo = boost::any_cast<map<string, double>>(*msg); //{key, value} pair
				_emotion = emo;
			}
			catch(const boost::bad_any_cast&){
			}
		}


	} break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::EVENT:  break;
	}
}

unsigned char app_picat::encode(map<string, double> emotion)
{
	//choose max probability
	double max_value = 0.0;
	string max_emotion = "";
	for(auto const& element:emotion){
		if(element.second>max_value){
			max_value = element.second;
			max_emotion = element.first;
		}
	}

	unsigned char code = 0x00;

//	//emotion code
	if(!max_emotion.compare("anger")) 			code = 0x01;
	else if(!max_emotion.compare("contempt")) code = 0x02;
	else if(!max_emotion.compare("disgust")) code = 0x03;
	else if(!max_emotion.compare("fear")) code = 0x04;
	else if(!max_emotion.compare("happiness")) code = 0x05;
	else if(!max_emotion.compare("sadness")) code = 0x06;
	else if(!max_emotion.compare("surprise")) code = 0x07;
	else code = 0x00;

	return code;
}


