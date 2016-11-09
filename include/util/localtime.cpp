
#include "localtime.hpp"

namespace cossb {
namespace util {
systime::systime()
{
	local();
}

systime::~systime()
{

}

string systime::current()
{
	local();
	string time = fmt::format("{}-{}-{} {}:{}:{}",
			_time.ctm_year,_time.ctm_mon,_time.ctm_mday,
			_time.ctm_hour,_time.ctm_min,_time.ctm_sec);
	return time;
}

stime* systime::get_time()
{
	return &_time;
}

stime* systime::local()
{
	std::time_t now = std::time(nullptr);
	tm* local = std::localtime(&now);

	_time.ctm_sec = local->tm_sec;
	_time.ctm_min = local->tm_min+1;
	_time.ctm_hour = local->tm_hour;
	_time.ctm_mday = local->tm_mday;
	_time.ctm_mon = local->tm_mon+1;
	_time.ctm_year = local->tm_year+1900;
	_time.ctm_wday = local->tm_wday;
	_time.ctm_yday = local->tm_yday;
	_time.ctm_isdst = local->tm_isdst;

	return &_time;
}

} /* namespace util */
} /* namespace cossb */
