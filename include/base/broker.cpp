#include "broker.hpp"
#include <base/message_any.hpp>
#include <interface/iprofile.hpp>

namespace cossb {
namespace broker {

unsigned int component_broker::publish(const char* service_name, cossb::message& msg)
{
	unsigned int times = 0;

	if(_service_map.find(service_name)!=_service_map.end()) {
		auto range = _topic_map.equal_range(_service_map[service_name].topic);

		msg.msg_frame.topic = _service_map[service_name].topic;
		for(topic_map::iterator itr = range.first; itr!=range.second; ++itr) {
			if(_service_map[itr->first].method == service::methodtype::SUBSCRIBE){
				driver::component_driver* _drv = cossb_component_manager->get_driver(itr->second.c_str());
				if(_drv){
					if(!_drv->mine(msg.get_from())) {
						cossb_log->log(log::loglevel::INFO, fmt::format("Subscribe {} : {} --> {}", msg.msg_frame.topic, msg.get_from(), _drv->get_component()->get_name()));
						_drv->subscribe(&msg);
						times++;
					}
				}
				else {
					cossb_log->log(log::loglevel::ERROR, fmt::format("{} service has no component driver. it will be removed.", service_name));
					_service_map.erase(service_name);
					//throw broker::exception(cossb::broker::excode::DRIVER_NOT_FOUND);
				}
			}
		}
	}
	else
		cossb_log->log(log::loglevel::ERROR, fmt::format("No Services({}) found", service_name));

	return times;
}

//template<typename... Args>
//unsigned int component_broker::publish(interface::icomponent* to_component, const char* topic, const char* api, const Args&... args)
//{
//	auto range = _topic_map.equal_range(topic);
//	unsigned int times = 0;
//	for(topic_map::iterator itr = range.first; itr!=range.second; ++itr) {
//		if(itr->second.compare(to_component->get_name())!=0) {
//			driver::component_driver* _drv = cossb_component_manager->get_driver(itr->second.c_str());
//			if(_drv) {
//				_drv->request(api, args...);
//				times++;
//			}
//			else {
//				cossb_log->log(log::loglevel::ERROR, fmt::format("<{}> has no component driver.", to_component->get_name()));
//				//throw broker::exception(cossb::broker::excode::DRIVER_NOT_FOUND);
//			}
//		}
//	}
//
//	return times;
//}

bool component_broker::regist(cossb::service::_service_desc* const service)
{
	if(service) {
		if(_service_map.find(service->name)==_service_map.end()) {
			_service_map.insert(service_map::value_type(service->name, *service));
			_topic_map.insert(topic_map::value_type(service->topic, service->component_name));
			cossb_log->log(log::loglevel::INFO, fmt::format("Service Registration : Topic [{}] / Service [{}]", service->topic, service->name));
			return true;
		}
		else
			cossb_log->log(log::loglevel::WARN, fmt::format("Already registered service : Topic {} / Service {}", service->topic, service->name));
	}

	return false;
}

} /* namespace broker */
} /* namespace cossb */
