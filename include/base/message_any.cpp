
#include "message_any.hpp"

namespace cossb {

void message::set(boost::any data){
		this->msg_frame.data = data;
	}

}
