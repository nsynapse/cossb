

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

/*class Date {
public:
	Date(int year, int month, int day):_year(year), _month(month), _day(day) {}
	friend std::ostream &operator<<(std::ostream &os, const Date &d) {
		return os << d._year_ << '-' << d._month_ << '-' << d._day_;
	}

	private:
	int _year, _month, _day;
};*/


class systime : public tm {
public:
	systime();
	virtual ~systime();

	string current();
	stime* get_time();

private:
	stime* local();

private:
	stime _time;

};

} /* namespace util */
} /* namespace cossb */

#endif /* _COSSB_UTIL_LOCALTIME_HPP_ */
