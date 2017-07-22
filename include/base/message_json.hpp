/**
 * @file		message.hpp
 * @brief		Message class using JSON
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 6
 * @details	component message class
 */

#ifndef _COSSB_MESSAGE_HPP_
#define _COSSB_MESSAGE_HPP_

#include <string>
#include <vector>
#include <ext/json.hpp>

using namespace std;

namespace cossb {
namespace broker { class component_broker; }
namespace driver { class component_driver; }
namespace interface { class icomponent; }
namespace base {

enum class msg_type : char {
		DATA = 0x01,	//send data
		SIGNAL,		//signal message(like event)
		REQUEST,		//request message
		RESPONSE		//response message
};

/**
 * @brief	serialized message frame
 */
typedef struct _msgframe {
	msg_type	type;
	vector<char> encoded_data;
	string topic;
	string from;
} msgframe;


/**
 * @brief	message interface class with json
 */
class message {
	using json = nlohmann::json;

	friend class cossb::broker::component_broker;
	friend class cossb::driver::component_driver;

public:
	message(interface::icomponent* component, msg_type type = msg_type::DATA);
	message(const char* component_name, msg_type type = msg_type::DATA);
	virtual ~message() { }

	inline json::reference operator[] (const char* k) {
		return data[k];
	}

	inline json::const_reference operator[] (const char* k) const {
		return data[k];
	}

	string raw(){
		return data.dump();
	}

	cossb::base::msgframe* get_frame() { return &frame; }
	const char* get_topic() { return frame.topic.c_str(); }
	const char* get_from() { return frame.from.c_str(); }

	/**
	 * @breif	message data parse to json format
	 */
	void parse(string sdata);

	/**
	 * @brief	check empty
	 * @return 	true if frame has no encoded data
	 */
	bool is_empty();	//true, if frame has no data

	/*
	 * @brief	find
	 */
	bool exist(const char* key) const;

	/**
	 * @brief	getting json data pointer
	 */
	inline json* get() {
		return &data;
	}

protected:
	/**
	 * @brief	serialize the json data
	 */
	void serialize() {
		string encode = data.dump();
		std::copy(encode.begin(), encode.end(), std::back_inserter(frame.encoded_data));
	}

protected:
	cossb::base::msgframe frame;
	json data;
};

} /* namespace base */
} /* namespace cossb */


#endif /* _COSSB_MESSAGE_HPP_ */
