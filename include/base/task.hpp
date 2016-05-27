/**
 * @file		task.hpp
 * @brief		base task(thread) using boost library
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 24
 * @details	COSSB task based on Boost library
 */
#ifndef _COSSB_TASK_HPP_
#define _COSSB_TASK_HPP_

//#if defined __BOOSTTHREAD__ || __boostthread__
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
/*#elif defined __TINYTHREAD__ || __tinythread__
#include <ext/tinythread.h>
#include <memory>
#endif*/

using namespace std;
using namespace boost;

namespace cossb {
namespace base {

//#if defined __BOOSTTHREAD__ || __boostthread__
	typedef boost::shared_ptr<boost::thread> task;
/*#elif defined __TINYTHREAD__ || __tinythread__
	typedef std::shared_ptr<thread> task;
#endif*/

#define task_register(fnptr)	boost::thread(boost::bind(fnptr, this))
#define create_task(fnptr)	boost::shared_ptr<boost::thread>(new task_register(&fnptr))
#define destroy_task(instance)	if(instance){ instance->interrupt(); instance->join(); }


} /* namespace base */
} /* namespace cossb */



#endif /* _COSSB_TASK_HPP_ */
