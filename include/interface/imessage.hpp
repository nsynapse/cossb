/**
 * @file		imessage.hpp
 * @brief		message interface
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2017. 7. 22
 * @details	Message interface
 */


#ifndef _COSSB_IMESSAGE_HPP_
#define _COSSB_IMESSAGE_HPP_

#include <string>
#include <tuple>

using namespace std;

namespace cossb {

namespace broker { class component_broker; }
namespace driver { class component_driver; }
namespace interface { class icomponent; }

namespace base {

/*
 * @brief	message type definitions
 */
enum class msg_type : char {
	DATA = 0x01,	//data (one way message)
	EVENT,		//event message (one way message)
	REQUEST,		//request message
	RESPONSE		//response message
};

/*
 * @brief	 message type structure
 */
template<typename _T>
struct msgframe {
	msg_type type;
	string topic;
	string from;		//message source name
	_T data;
};
}


namespace interface {

/*
 * @brief message interface class
 */

template<typename _T>
class imessage {

	friend class cossb::broker::component_broker;
	friend class cossb::driver::component_driver;

public:
	imessage(const char* component_name, base::msg_type type = base::msg_type::DATA){ }
	imessage(interface::icomponent* component, base::msg_type type = base::msg_type::DATA){ }
	virtual ~imessage() { }

	/*
	 * @brief	 support functions
	 */

	base::msgframe<_T>* get_frame() { return &msg_frame; }

	_T* get_data() { return &msg_frame.data; }

	/*
	 * @brief	get message topic
	 */
	const char* get_topic() const { return msg_frame.topic.c_str(); }

	/*
	 * @brief
	 */
	const char* get_from() const { return msg_frame.from.c_str(); }

	/*
	 * @brief
	 */
	void set(_T& data){  msg_frame.data = data; }

	/*
	 * @brief
	 */
	base::msg_type get_type() const { return msg_frame.type; }

	/*
	 * @brief	(interface) check if message data is empty
	 */
	virtual bool is_empty() = 0;

	/*
	 * @brief	(interface) message data clear
	 */
	virtual void clear() = 0;

protected:
	base::msgframe<_T> msg_frame;

};

} /* namespace interface */
} /* namespace cossb */

#endif
