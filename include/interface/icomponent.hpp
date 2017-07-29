/**
 * @file		icomponent.hpp
 * @brief		Component(Shared Library) interface
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details		Component interface class
 */

#ifndef _COSSB_ICOMPONENT_HPP_
#define _COSSB_ICOMPONENT_HPP_

#include <string>
#include <interface/iprofile.hpp>
#include <interface/ilog.hpp>
//#include <interface/imessage.hpp>
#include <base/message_any.hpp>
#include <cassert>

using namespace std;

namespace cossb {

namespace component {
	enum class status : unsigned int { IDLE=0, RUNNING, STOPPED };
}

namespace driver { class component_driver; }

namespace interface {
/**
* @brief		component interface class
* @details		base component interface, lifecycle is (setup-run-stop)
* @author		Byunghun Hwang<bhhwang@nsynapse.com>
* @date		2015. 6. 22
*/
class icomponent {

	friend driver::component_driver;

public:
	/**
	 * @brief
	 */
	virtual ~icomponent() {
		if(_profile)
			delete _profile;

		if(_logger)
			delete _logger;
	}

	/**
	 * @brief		initialization
	 * @details	this function will be called once when load component
	 * @return		true if it is success
	 */
	virtual bool setup() = 0;

	/**
	 * @brief		start signal comes in, this function will be called
	 * @details
	 */
	virtual bool run() = 0;

	/**
	 * @brief	stop interface
	 * @brief	stop signal comes in, this function will be called
	 */
	virtual bool stop() = 0;

	/**
	 * @brief	message request
	 * @details	if request message comes in, this function will be called
	 */
//	virtual void request(cossb::base::message* const msg) = 0;
	void request(cossb::message* const msg){ }

	/**
	 * @brief
	 */
	const char* get_name() const {
		return _name.c_str();
	}

	/**
	 * @brief
	 */
	iprofile* get_profile() const {
		return _profile;
	}

	/**
	 * @brief	getting status
	 */
	component::status get_status() { return _status; }

protected:
	explicit icomponent(const char* name)
	:_name(name), _status(component::status::IDLE) {

	}

private:
	/**
	 * @brief	component name
	 */
	string _name;

	/*
	 * @brief	interval
	 */


	/**
	 * @brief	component profile interface
	 */
	iprofile* _profile = nullptr;

	/**
	 * @brief	component log interface
	 */
	ilog* _logger = nullptr;

protected:
	component::status _status;

	ilog* logger() {
		assert(_logger!=nullptr);
		return _logger;
	}

};

} /* namespace interface */


typedef interface::icomponent*(*create_component)(void);
typedef void(*destroy_component)(void);

/**
 * @brief	Component interface macro
 */
#define USE_COMPONENT_INTERFACE(classname)	static classname* _instance = nullptr; \
											cossb::interface::icomponent* create() { if(_instance==nullptr) _instance = new classname(); return _instance; } \
											void destroy(){ if(_instance!=nullptr){ delete _instance; _instance=nullptr; }}


#define COMPONENT_EXPORT				extern "C" { cossb::interface::icomponent* create(); void destroy(void); }

#define COMPONENT(classname) #classname

} /* namespace cossb */


#endif /* _COSSB_ICOMPONENT_HPP_ */
