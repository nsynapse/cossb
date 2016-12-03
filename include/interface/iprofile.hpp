/**
 * @file		iprofile.hpp
 * @brief		Component Profile interface class
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Read component profile interface
 */


#ifndef _COSSB_IPROFILE_HPP_
#define _COSSB_IPROFILE_HPP_

#include <string>
#include <vector>
#include <map>
#include <boost/lexical_cast.hpp>
#include <cstring>
#include <algorithm>
#include <util/format.h>
#include <util/uuid.hpp>


using namespace std;
using namespace cossb;

namespace cossb {
namespace service {

/**
 * @brief	service method type
 */
enum class methodtype : int {
	PUBLISH = 1,
	SUBSCRIBE,
	UNDEFINED,
};

/**
 * @brief	service method
 */
typedef struct _service_method {
public:
	_service_method():method(methodtype::UNDEFINED) {}
	_service_method(const char* type) {
		if(strcmp(type, "publish")==0)
			method = methodtype::PUBLISH;
		else if(strcmp(type, "subscribe")==0)
			method = methodtype::SUBSCRIBE;
	}
	const char* str() {
		string mt = "Undefined";
		switch(method) {
		case methodtype::PUBLISH: mt = "Publish"; break;
		case methodtype::SUBSCRIBE: mt = "Subscribe"; break;
		case methodtype::UNDEFINED: mt = "Undefined"; break;
		}
		return mt.c_str();
	}
	_service_method& operator= (_service_method const& m) { this->method = m.method; return *this; }
private:
	methodtype method = methodtype::UNDEFINED;
} service_method;

/**
 * @brief	service description
 */

typedef struct _service_desc {
private:
	util::uuid service_id;	//service id
public:
	string component_name;	//component name
	string name;				//service name
	service_method method;	//service method
	string topic;				//service topic
	const char* raw() {
		return fmt::format("[{}] Name : {}, Method : {}, Topic : {}", service_id.str(), name, method.str(), topic).c_str();
	}
} service_desc;

/**
 * @brief	profile service section container
 */
typedef vector<service::service_desc> service_desc_container;

} /* namespace service */

namespace interface { class iprofile; }

namespace profile {

/**
 * @brief	profile information section container
 */
//typedef map<string, string> profile_info_container;

enum class section : unsigned int {
	info = 0,	//component information
	property, 	//properties
	resource,	//related resource
	service,	//service supporting
};

class type_value
{
public:
	type_value():value("") { }
	type_value(const char* val) { this->value = val; }
	virtual ~type_value() { }

	friend class interface::iprofile;

	template<typename T>
	inline T as(T default_value) {
		try {
			T val = boost::lexical_cast<T>(value);
			return val;
		} catch( boost::bad_lexical_cast const& ) {
			return default_value;
		}
	}

	int asInt(int default_value) { return as(default_value); }
	unsigned int asUInt(unsigned int default_value) { return as(default_value); }
	unsigned long asUlong(unsigned long default_value) { return as(default_value); }
	double asDouble(double default_value) { return as(default_value); }
	float asFloat(float default_value) { return as(default_value); }
	bool asBool(bool default_value) { return as(default_value); }
	string asString(string default_value) { return as(default_value); }
	unsigned char asUChar(unsigned char default_value) { return as(default_value); }
	char asChar(char default_value) { return as(default_value); }

private:
	std::string value;

};
}

namespace driver { class component_driver; }
namespace manager { class component_manager; }

namespace interface {
class icomponent;
class iprofile {

	friend class driver::component_driver;
	friend class manager::component_manager;

public:
	iprofile() { }
	virtual ~iprofile() {
		_services.clear();
	}

	/**
	 * @brief	get profile value list
	 */
	virtual vector<profile::type_value> gets(profile::section section, const char* element) = 0;


	/**
	 * @brief	get profile value
	 */
	virtual profile::type_value get(profile::section section, const char* element) = 0;

	/**
	 * @brief	get attribute in element
	 */
	//virtual profile::type_value get_attribute(string& node, const char* attr) = 0;


	/**
	 * @brief	update profile value
	 */
	virtual bool update(profile::section section, const char* element, const char* value) = 0;

	/**
	 * @brief	save profile
	 */
	virtual bool save() = 0;


private:
	/**
	 * @brief	load profile
	 */
	virtual bool load(icomponent* pComponent, const char* filepath) = 0;

protected:
	/**
	 * @brief
	 */
	void set(profile::type_value& profile, string value) { profile.value = value; }

	/**
	 * @brief	insert into the service container
	 * @return total number of services registered
	 */
	int add(service::service_desc& svc) {
		_services.push_back(svc);
		return _services.size();
	}

private:

	/**
	 * @brief	service description container
	 */
	service::service_desc_container _services;

};

} /* namespace interface */
} /* namespace cossb */

#endif
