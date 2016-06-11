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

class isql
{
public:
	virtual ~isql() {}

	/*
	 * @brief	send sql query
	 */
	virtual void query(const char* q) = 0;
};

} /* namespace interface */
} /* namespace cossb */



#endif /* _COSSB_INTERFACE_ISQL_HPP_ */
