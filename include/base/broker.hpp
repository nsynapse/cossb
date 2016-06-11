/**
 * @file		broker.hpp
 * @brief		Component Broker
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details
 */

#ifndef _COSSB_BROKER_HPP_
#define _COSSB_BROKER_HPP_

#include <map>
#include <string>
#include <interface/icomponent.hpp>
#include <interface/iprofile.hpp>
#include <arch/singleton.hpp>
#include <base/manager.hpp>
#include <base/log.hpp>
#include <base/exception.hpp>
#include <base/message.hpp>

using namespace std;
using namespace cossb;

namespace cossb {
namespace driver { class component_driver; }
namespace manager { class component_manager; }
namespace broker {

//topic, component name
typedef multimap<string, string> topic_map;

//service name, service desc
typedef map<string, service::_service_desc> service_map;


class component_broker : public arch::singleton<component_broker> {

	friend class component_driver;
	friend class component_manager;

public:
	component_broker() { };
	virtual ~component_broker() {
		_topic_map.clear();
		_service_map.clear();
	};

	/**
	 * @brief	publish message to
	 */
	unsigned int publish(const char* service_name, cossb::base::message& msg);


	/**
	 * @brief		publish data pack to specific service component
	 * @return		times published
	 */
	template<typename... Args>
	unsigned int publish(interface::icomponent* to_component, const char* topic, const char* api, const Args&... args);

	/**
	 * @brief	regist component to broker
	 */
	bool regist(cossb::service::_service_desc* const service);


private:

	/**
	 * @brief	Topic map to find component
	 */
	topic_map	_topic_map;

	/**
	 * @brief	Service map
	 */
	service_map _service_map;
};

#define cossb_broker		cossb::broker::component_broker::instance()

} /* namespace broker */
} /* namespace cossb */

#endif
