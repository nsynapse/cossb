

#ifndef _COSSB_UTIL_LOCALTIME_HPP_
#define _COSSB_UTIL_LOCALTIME_HPP_

#include <ctime>
#include <string>
#include "format.h"

using namespace std;

namespace cossb {
namespace util {

typedef struct _stime {
	int ctm_sec;
	int ctm_min;
	int ctm_hour;
	int ctm_mday;
	int ctm_mon;
	int ctm_year;
	int ctm_wday;
	int ctm_yday;
	int ctm_isdst;
} stime;

class systime : public tm {
public:
	systime();
	virtual ~systime();

	string current();
	string current_formatted();
	stime* get_time();

private:
	stime* local();

private:
	stime _time;

};

} /* namespace util */
} /* namespace cossb */

#endif /* _COSSB_UTIL_LOCALTIME_HPP_ */
