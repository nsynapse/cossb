#include "broker.hpp"

namespace cossb {
namespace broker {

unsigned int component_broker::publish(const char* service_name, cossb::base::message& msg)
{
	unsigned int times = 0;

	if(_service_map.find(service_name)!=_service_map.end()) {
		cout << "find topic : " << _service_map[service_name].topic << endl;

		auto range = _topic_map.equal_range(_service_map[service_name].topic);
		for(topic_map::iterator itr = range.first; itr!=range.second; ++itr) {
			driver::component_driver* _drv = cossb_component_manager->get_driver(itr->second.c_str());
			cout << "dd"<<endl;
			if(_drv) {
				cout << "request" << msg.show() << endl;
				_drv->request(&msg);
				times++;
			}
			else
				throw broker::exception(cossb::broker::excode::DRIVER_NOT_FOUND);
		}
	}
	else
		cossb_log->log(log::loglevel::ERROR, "No Services found");

	return times;
}

template<typename... Args>
unsigned int component_broker::publish(interface::icomponent* to_component, const char* topic, const char* api, const Args&... args)
{
	auto range = _topic_map.equal_range(topic);
	unsigned int times = 0;
	for(topic_map::iterator itr = range.first; itr!=range.second; ++itr) {
		if(itr->second.compare(to_component->get_name())!=0) {
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

bool component_broker::regist(cossb::service::_service_desc* const service)
{
	if(service) {
		if(_service_map.find(service->name)==_service_map.end()) {
			_service_map.insert(service_map::value_type(service->name, *service));
			_topic_map.insert(topic_map::value_type(service->topic, service->component_name));
			return true;
		}
	}

	return false;
}

} /* namespace broker */
} /* namespace cossb */
