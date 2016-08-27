/**
 * @file		profile.hpp
 * @brief		XML type component profile
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details		XML component profile
 */

#ifndef _COSSB_PROFILE_HPP_
#define _COSSB_PROFILE_HPP_

#include <string>
#include <interface/iprofile.hpp>
#include <ext/tinyxml2.h>

using namespace std;
using namespace tinyxml2;

namespace cossb {
namespace interface { class icomponent; }
namespace profile {

class xml : public interface::iprofile {
public:
	xml();
	virtual ~xml();

	/**
	 * @brief	getting profile value list
	 */
	vector<profile::type_value> gets(profile::section section, const char* element);
	//vector<string> gets(profile::section section, const char* element);


	/**
	 * @brief	get attribute in element
	 */
	profile::type_value get_attribute(profile::section section, const char* element, const char* attr);


	/**
	 * @brief	getting profile value
	 */
	profile::type_value get(profile::section section, const char* element);

	/**
	 * @brief	update
	 */
	bool update(profile::section section, const char* element, const char* value);


	/**
	 * @brief	save
	 */
	bool save();

private:
	/**
	 * @brief	load xml profile
	 */
	bool load(interface::icomponent* pComponent, const char* filepath);

private:

	/**
	 * @brief	read services
	 */
	void read_services(interface::icomponent* pComponent);

	/**
	 * @brief	getting comment what error is occurred
	 */
	const char* get_error_str(int error) const;

private:
	XMLDocument* _doc = nullptr;

	bool _loaded = false;
	string _filepath;
};

} /* namespace profile */
} /* namespace cossb */

#endif /* _COSSB_PROFILE_HPP_ */
