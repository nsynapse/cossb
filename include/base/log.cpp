
#include "log.hpp"
#include <iostream>
#include <interface/ilog.hpp>
#include <util/format.h>


namespace cossb {
namespace log {

#define _COLOR_ERROR_	"\033[1;31m"
#define _COLOR_END_		"\033[0m"

console::console(){ }
console::console(interface::ilog* log):_logger(log) { }

console::~console() {
	_logger = nullptr;

}

void console::log(const log::loglevel& level, const char* logstr)
{
	if(_logger)
		_logger->log(level, logstr);
	else
	{
		switch(level)
		{
		case	loglevel::TRACE:	cout << "[" << _time.current() << "]" << "[TRACE]\t"	<< logstr << endl;	break;
		case	loglevel::DEBUG:	cout << "[" << _time.current() << "]" << "[DEBUG]\t"	<< logstr << endl;	break;
		case	loglevel::INFO:		cout << "[" << _time.current() << "]" << "[INFO]\t"		<< logstr << endl;	break;
		case	loglevel::NOTICE: 	cout << "[" << _time.current() << "]" << "[NOTICE]\t"	<< logstr << endl;	break;
		case	loglevel::WARN: 	cout << "[" << _time.current() << "]" << "[WARN]\t"		<< logstr << endl;	break;
		case	loglevel::ERROR: 	cout << _COLOR_ERROR_ << "[" << _time.current() << "]" << "[ERROR]\t"	<< logstr << _COLOR_END_ << endl;	break;
		case	loglevel::CRITICAL: cout << "[" << _time.current() << "]" << "[CRITICAL]\t"	<< logstr << endl;	break;
		case	loglevel::ALERT: 	cout << "[" << _time.current() << "]" << "[ALERT]\t"	<< logstr << endl;	break;
		case	loglevel::EMERG: 	cout << "[" << _time.current() << "]" << "[EMERG]\t"	<< logstr << endl;	break;
		}
	}
}

void console::log(const log::loglevel& level, string logstr)
{
	if(_logger)
		_logger->log(level, logstr.c_str());
	else
	{
		switch(level)
		{
		case	loglevel::TRACE:	cout << "[" << _time.current() << "]" << "[TRACE]\t"	<< logstr << endl;	break;
		case	loglevel::DEBUG:	cout << "[" << _time.current() << "]" << "[DEBUG]\t"	<< logstr << endl;	break;
		case	loglevel::INFO:		cout << "[" << _time.current() << "]" << "[INFO]\t"		<< logstr << endl;	break;
		case	loglevel::NOTICE: 	cout << "[" << _time.current() << "]" << "[NOTICE]\t"	<< logstr << endl;	break;
		case	loglevel::WARN: 	cout << "[" << _time.current() << "]" << "[WARN]\t"		<< logstr << endl;	break;
		case	loglevel::ERROR: 	cout << _COLOR_ERROR_ << "[" << _time.current() << "]" << "[ERROR]\t"	<< logstr << _COLOR_END_ << endl;	break;
		case	loglevel::CRITICAL: cout << "[" << _time.current() << "]" << "[CRITICAL]\t"	<< logstr << endl;	break;
		case	loglevel::ALERT: 	cout << "[" << _time.current() << "]" << "[ALERT]\t"	<< logstr << endl;	break;
		case	loglevel::EMERG: 	cout << "[" << _time.current() << "]" << "[EMERG]\t"	<< logstr << endl;	break;
		}
	}
}

void console::adopt(interface::ilog* intlog)
{
	_logger = intlog;
}

} /* namespace log */
} /* namespace cossb */
