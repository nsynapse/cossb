
#include "nanopi.hpp"
#include <cossb.hpp>

using namespace std;

USE_COMPONENT_INTERFACE(nanopi)

nanopi::nanopi()
:cossb::interface::icomponent(COMPONENT(nanopi)){
	// TODO Auto-generated constructor stub

}

nanopi::~nanopi() {

}

bool nanopi::setup()
{


	return true;
}

bool nanopi::run()
{

}

bool nanopi::stop()
{

	return true;
}

void nanopi::subscribe(cossb::message* const msg)
{
	switch(msg->get_frame()->type) {
		case cossb::base::msg_type::REQUEST: break;
		case cossb::base::msg_type::DATA: {

			//subscribe emotion data
			try {

			}
			catch(const boost::bad_any_cast&){
				cossb_log->log(log::loglevel::ERROR, "Invalid type casting, should be map<int, unsigned char> type.");
			}
		} break;
		case cossb::base::msg_type::RESPONSE: break;
		case cossb::base::msg_type::EVENT:  break;
		}
}


