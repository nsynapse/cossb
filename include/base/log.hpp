/**
 * @file		log.hpp
 * @brief		cossb default console logger
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 9
 * @details		COSSB default logger
 */
#ifndef _COSSB_LOG_HPP_
#define _COSSB_LOG_HPP_

#include <arch/singleton.hpp>
#include <util/format.h>
#include <interface/ilog.hpp>
#include <util/localtime.hpp>

namespace cossb {
namespace manager { class system_manager; }
namespace log {

class console : public arch::singleton<console>
{

	friend class manager::system_manager;

public:
	console();
	console(interface::ilog* log);
	virtual ~console();

	/**
	 * @brief	simple log interface function
	 */
	void log(const loglevel& level,  const char* logstr);
	void log(const log::loglevel& level, string logstr);

	/**
	 * @brief	to use another log interface dynamically
	 */
	void adopt(interface::ilog* intlog);

private:

	/**
	 * @brief	default log base function
	 */
	void log_base(const loglevel level, const char* str);


private:
	interface::ilog* _logger = nullptr;

	util::systime _time;

};

#define cossb_log		cossb::log::console::instance()

} /* namespace log */
} /* namespace cossb */

#endif /* _COSSB_LOGGER_HPP_ */
