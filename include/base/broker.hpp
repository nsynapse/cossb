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
#include <arch/singleton.hpp>
#include <base/manager.hpp>
#include <base/log.hpp>
#include <base/exception.hpp>
#include <base/message.hpp>

using namespace std;

namespace cossb {
namespace driver { class component_driver; }
namespace broker {

//(topic, component name) pair
typedef multimap<string, string> topic_map;

class component_broker : public arch::singleton<component_broker> {

	friend class component_driver;

public:
	component_broker() { };
	virtual ~component_broker() { };

	/**
	 * @brief	publish message
	 */
	unsigned int publish(cossb::base::message& msg) {
		auto range = _topic_map.equal_range(msg.get_topic());
		unsigned int times = 0;
		for(topic_map::iterator itr = range.first; itr!=range.second; ++itr) {
			if(itr->second.compare(msg.get_from())!=0) {
				driver::component_driver* _drv = cossb_component_manager->get_driver(itr->second.c_str());
				if(_drv) {
					cossb_log->log(log::loglevel::INFO, fmt::format("publish to : {}", msg.get_topic()).c_str());
					_drv->request(&msg);
					times++;
				}
				else
					throw broker::exception(cossb::broker::excode::DRIVER_NOT_FOUND);
			}
		}

		return times;
	}

	/**
	 * @brief		publish data pack to specific service component
	 * @return		times published
	 */
	template<typename... Args>
	unsigned int publish(interface::icomponent* component, const char* to_topic, const char* api, const Args&... args) {
		auto range = _topic_map.equal_range(to_topic);
		unsigned int times = 0;
		for(topic_map::iterator itr = range.first; itr!=range.second; ++itr) {
			if(itr->second.compare(component->get_name())!=0) {
				driver::component_driver* _drv = cossb_component_manager->get_driver(itr->second.c_str());
				if(_drv) {
					_drv->request(api, args...);
					times++;
				}
				else
					throw broker::exception(cossb::broker::excode::DRIVER_NOT_FOUND);
			}
		}

		return times;
	}

private:
	/**
	 *@brief	regist component with topic
	 */
	bool regist(interface::icomponent* component, string topic_name) {
		auto range = _topic_map.equal_range(topic_name);
		bool found = false;
		for(topic_map::iterator itr = range.first; itr!=range.second; ++itr) {
			if(itr->second.compare(component->get_name())==0)
				found = true;
		}
		if(!found) {
			cossb_log->log(log::loglevel::INFO, fmt::format("Topic registered : {}", topic_name).c_str());
			_topic_map.insert(topic_map::value_type(topic_name, component->get_name()));
		}
		else
			cossb_log->log(log::loglevel::WARN, fmt::format("Already registered topic : {}", topic_name).c_str());


		return true;
	}

	/**
	 * @brief	regist component
	 */
	bool regist(interface::icomponent* component, interface::iprofile* profile) {
		if(profile) {
			//profile->
		}
		return false;
	}

private:
	topic_map	_topic_map;
};

#define cossb_broker		cossb::broker::component_broker::instance()

} /* namespace broker */
} /* namespace cossb */

#endif
