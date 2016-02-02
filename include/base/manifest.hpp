/**
 * @file		manifest.hpp
 * @brief		COSSB manifest reader
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details		Load xml manifest file
 */

#ifndef _COSSB_MANIFEST_HPP_
#define _COSSB_MANIFEST_HPP_

#include <arch/singleton.hpp>
#include <tinyxml2.h>
#include <vector>
#include <string>
#include <map>

using namespace tinyxml2;
using namespace std;

namespace cossb {
namespace driver { class component_driver; }
namespace broker { class component_broker; }

namespace base {

enum class bundleType : unsigned int {
	COMPONENT=1, 	/* component */
	LIBRARY, 		/* library */
	PACKAGE 		/* component+library package */
};

typedef struct _req_element {
	bundleType type;
	std::string name;

public:
	_req_element(bundleType _type, string _name):type(_type),name(_name) { }
	_req_element& operator=(const _req_element& other) { return *this; }
} req_element;



/**
 * @brief	manifest reader class
 */
class manifestreader : public arch::singleton<manifestreader> {

	friend class driver::component_driver;
	friend class broker::component_broker;

public:
	manifestreader();
	virtual ~manifestreader();

	/**
	 * @brief	load configurations to apply user-defined parameters
	 */
	bool load(const char* manifest_file);

	/**
	 * @brief	getting manifest information
	 */
	vector<req_element*>& get_required() { return _required; }

	/**
	 * @brief	getting manifest repository
	 */
	vector<string>& get_repository() { return _repository; }

	/**
	 * @brief	getting path property
	 */
	map<string, string>& get_path() { return _path; }

	/**
	 * @brief	getting product information
	 */
	map<string, string>& get_product_info() { return _product; }

	/**
	 * @brief	enabled parameter
	 */
	bool is_enabled(const char* name) {
		if(_enable.find(name)==_enable.end())
			return false;
		return true;
	}

private:
	/**
	 * @brief	read information from manifest file
	 */
	void read_info();

	/**
	 * @brief	read required components and libraries
	 */
	void read_required();

	/**
	 * @brief	read system parameters and options
	 */
	void read_system();

	/**
	 * @brief	read auth properties
	 */
	void read()

private:
	void parse_path();
	void parse_repository();
	void parse_product_info();


private:
	/**
	 * @brief	xml-type manifest document
	 */
	tinyxml2::XMLDocument* _doc = nullptr;

	/**
	 * @brief	info section
	 */
	map<string, string>	_info;

	/**
	 * @brief	required section
	 */
	vector<req_element*> _required;

	/**
	 * @brief	system section
	 */
	map<string, bool> _enable;

	vector<string> _repository;
	map<string, string> _path;
	map<string, string> _product;

};

#define cossb_manifest		cossb::base::manifestreader::instance()

} /* namespace base */
} /* namespace cossb */

#endif /* _COSSB_MANIFEST_HPP_ */
