/*
 * sqlite.hpp
 *
 *  Created on: 2016. 6. 11.
 *      Author: hwang
 */

#ifndef _COSSB_DB_SQLITE_HPP_
#define _COSSB_DB_SQLITE_HPP_

#include <interface/idatabase.hpp>
#include <interface/isql.hpp>

namespace cossb {
namespace db {

class sqlite : public interface::isql, interface::idatabase {
public:
	sqlite();
	virtual ~sqlite();
};

}
}



#endif /* _COSSB_DB_SQLITE_HPP_ */
