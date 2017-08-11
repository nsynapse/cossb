

#include "emotion_adapter.hpp"
#include <cossb.hpp>
#include <3rdparty/bcm2835.h>

using namespace std;

USE_COMPONENT_INTERFACE(emotion_adapter)

emotion_adapter::emotion_adapter()
:cossb::interface::icomponent(COMPONENT(emotion_adapter)){
	// TODO Auto-generated constructor stub

}

emotion_adapter::~emotion_adapter() {

}

bool emotion_adapter::setup()
{
	_gpio = get_profile()->get(profile::section::property, "gpio").asInt(-1);

	return true;
}

bool emotion_adapter::run()
{

	return true;
}

bool emotion_adapter::stop()
{
	if(!bcm2835_close())
		return false;

	return true;
}

void emotion_adapter::subscribe(cossb::message* const msg)
{
	switch(msg->get_frame()->type) {
		case cossb::base::msg_type::REQUEST: break;
		case cossb::base::msg_type::DATA: {

			//subscribe
			try {
				map<int, unsigned char> data = boost::any_cast<map<int, unsigned char>>(*msg); //{key, value} pair

				//1. extract keys
				vector<int> keys;
				for(auto const& port: data)
					keys.push_back(port.first);

				//2. compare
				for(auto const& key:keys){
					if(key==_gpio){
						cossb::message msg(this, cossb::base::msg_type)
					}
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


