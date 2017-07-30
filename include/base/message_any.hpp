/**
 * @file		message_any.hpp
 * @brief		Message class for any type of data
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2017. 7. 22
 * @details	component message class for any type of data
 */

#ifndef _COSSB_MESSAGE_ANY_HPP_
#define _COSSB_MESSAGE_ANY_HPP_

#include <string>
#include <queue>
#include <boost/any.hpp>
#include <interface/imessage.hpp>

using namespace std;

namespace cossb {


/**
 * @brief	message class with boost::any
 */

class message : public cossb::interface::imessage<boost::any> {

public:
	message(const char* component_name, base::msg_type type);
	message(interface::icomponent* component, base::msg_type type);
	virtual ~message();

	/*
	 * @brief	message interface functions
	 */
	bool is_empty() {
		return false;
	}
	void clear() {  }

	void set(boost::any data);


};

} /* namespace cossb */


#endif /* _COSSB_MESSAGE_ANY_HPP_ */
