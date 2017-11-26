
#include "timboprotocol.hpp"
#include <cossb.hpp>
#include <string>

using namespace std;

USE_COMPONENT_INTERFACE(timboprotocol)

timboprotocol::timboprotocol()
:cossb::interface::icomponent(COMPONENT(timboprotocol)){
	// TODO Auto-generated constructor stub

}

timboprotocol::~timboprotocol() {

}

bool timboprotocol::setup()
{

	return true;
}

bool timboprotocol::run()
{

	return true;
}

bool timboprotocol::stop()
{

	return true;
}

void timboprotocol::subscribe(cossb::message* const msg)
{
	switch(msg->get_frame()->type) {
	case cossb::base::msg_type::REQUEST: break;
	case cossb::base::msg_type::DATA: {
		try
		{
			vector<unsigned char> data = boost::any_cast<vector<unsigned char>>(*msg->get_data());

			//push back into the buffer
			for(auto& d:data)
				_buffer.push_back(d);

			while(_buffer.size()>0){
				//align data buffer
				for(int i=0;i<_buffer.size();i++){
					if(_buffer.front()!=0x55) _buffer.pop_front();
					else
						break;
				}

				//extract data from the aligned data frame
				vector<unsigned char> extracted;
				if(_buffer.size()>=(int)_buffer[1]+3){
					extracted.assign(_buffer.begin(), _buffer.begin()+_buffer[1]+3);
				}

				//pop the data
				for(int i=0;i<extracted.size();i++)
					_buffer.pop_front();

				cossb_log->log(log::loglevel::INFO, fmt::format("aligned {} byte(s) from data", extracted.size()));
			}
		}
		catch(const boost::bad_any_cast&){
			cossb_log->log(log::loglevel::ERROR, "Invalid type casting");
		}
	} break;
	case cossb::base::msg_type::RESPONSE: break;
	}
}

}
