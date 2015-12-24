/**
 * @file		isql.hpp
 * @brief		interface class for SQL database
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 6
 * @details	interface class for database which is locally embeddable
 */

#ifndef _COSSB_INTERFACE_ISQL_HPP_
#define _COSSB_INTERFACE_ISQL_HPP_

namespace cossb {
namespace interface {

class iSQL
{
public:
	virtual ~iSQL() {}

	virtual bool open(const char* db) = 0;
	virtual void close() = 0;
};

} /* namespace interface */
} /* namespace cossb */



#endif /* _COSSB_INTERFACE_ISQL_HPP_ */
