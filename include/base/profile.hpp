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
#include <tinyxml2.h>

using namespace std;
using namespace tinyxml2;

namespace cossb {
namespace profile {


class xml : public interface::iprofile {
public:
	xml(const char* filepath=nullptr);
	virtual ~xml();

	/**
	 * @brief	getting profile value with matched type
	 */
	type_value get(profile::section section, const char* element);

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
	bool load(const char* filepath);

private:

	/**
	 * @brief	read profile
	 */
	void read_profile();

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
