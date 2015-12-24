
#include "log.hpp"
#include <iostream>
#include <interface/ilog.hpp>
#include <util/format.h>

namespace cossb {
namespace log {

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
		case	loglevel::TRACE:	cout << "[TRACE]\t"	<< logstr << endl;	break;
		case	loglevel::DEBUG:	cout << "[DEBUG]\t"	<< logstr << endl;	break;
		case	loglevel::INFO:	cout << "[INFO]\t"	<< logstr << endl;	break;
		case	loglevel::NOTICE: cout << "[NOTICE]\t"	<< logstr << endl;	break;
		case	loglevel::WARN: cout << "[WARN]\t"	<< logstr << endl;	break;
		case	loglevel::ERROR: cout << "[ERROR]\t"	<< logstr << endl;	break;
		case	loglevel::CRITICAL: cout << "[CRITICAL]\t"	<< logstr << endl;	break;
		case	loglevel::ALERT: cout << "[ALERT]\t"	<< logstr << endl;	break;
		case	loglevel::EMERG: cout << "[EMERG]\t"	<< logstr << endl;	break;
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
		case	loglevel::TRACE:	cout << "[TRACE]\t"	<< logstr << endl;	break;
		case	loglevel::DEBUG:	cout << "[DEBUG]\t"	<< logstr << endl;	break;
		case	loglevel::INFO:	cout << "[INFO]\t"	<< logstr << endl;	break;
		case	loglevel::NOTICE: cout << "[NOTICE]\t"	<< logstr << endl;	break;
		case	loglevel::WARN: cout << "[WARN]\t"	<< logstr << endl;	break;
		case	loglevel::ERROR: cout << "[ERROR]\t"	<< logstr << endl;	break;
		case	loglevel::CRITICAL: cout << "[CRITICAL]\t"	<< logstr << endl;	break;
		case	loglevel::ALERT: cout << "[ALERT]\t"	<< logstr << endl;	break;
		case	loglevel::EMERG: cout << "[EMERG]\t"	<< logstr << endl;	break;
		}
	}
}

void console::adopt(interface::ilog* intlog)
{
	_logger = intlog;
}

} /* namespace log */
} /* namespace cossb */
