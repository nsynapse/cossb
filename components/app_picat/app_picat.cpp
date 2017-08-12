
#include "app_picat.hpp"
#include <cossb.hpp>

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

		//* gpio read subscribe
		try {
			map<int, unsigned char> gpio_data = boost::any_cast<map<int, unsigned char>>(*msg); //{key, value} pair

			if(gpio_data.find(_gpio_trigger)!=gpio_data.end()){
				unsigned char read = gpio_data[_gpio_trigger];
				if(_prev_read==0x00 && read!=0x00){
					unsigned short code = encode(_emotion);

					cossb::message msg(this, cossb::base::msg_type::DATA);
					msg.pack(code);
					cossb_broker->publish("picat_gpio_write", msg);
				}
				_prev_read = read;
			}
		}
		catch(const boost::bad_any_cast&){
			cossb_log->log(log::loglevel::ERROR, "Invalid type casting, should be map<int, unsigned char> type.");
		}
	} break;
	case cossb::base::msg_type::RESPONSE: break;
	case cossb::base::msg_type::EVENT:  break;
	}
}

unsigned short app_picat::encode(map<string, double> emotion)
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
//	if(!max_emotion.compare("anger")) 	{ gpio_write[5] = 0x00; gpio_write[6] = 0x00; gpio_write[13] = 0x01; }
//	else if(!max_emotion.compare("contempt")){ gpio_write[5] = 0x00; gpio_write[6] = 0x01; gpio_write[13] = 0x00; }
//	else if(!max_emotion.compare("disgust")) { gpio_write[5] = 0x00; gpio_write[6] = 0x01; gpio_write[13] = 0x01; }
//	else if(!max_emotion.compare("fear")) 	{ gpio_write[5] = 0x01; gpio_write[6] = 0x00; gpio_write[13] = 0x00; }
//	else if(!max_emotion.compare("happiness")){gpio_write[5] = 0x01; gpio_write[6] = 0x00; gpio_write[13] = 0x01; }
//	else if(!max_emotion.compare("sadness")) { gpio_write[5] = 0x01; gpio_write[6] = 0x01; gpio_write[13] = 0x00; }
//	else if(!max_emotion.compare("surprise")){ gpio_write[5] = 0x01; gpio_write[6] = 0x01; gpio_write[13] = 0x01; }
//	else { gpio_write[5] = 0x00; gpio_write[6] = 0x00; gpio_write[13] = 0x00; } //neutral and else
//
//	return gpio_write;
}


