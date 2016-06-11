/**
 * @file		idatabase.hpp
 * @brief		interface class for database
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2016. 6. 11
 * @details		interface for database
 */

#ifndef _COSSB_INTERFACE_IDATABASE_HPP_
#define _COSSB_INTERFACE_IDATABASE_HPP_

namespace cossb {
namespace interface {

class idatabase
{
public:
	virtual ~idatabase() {}

	/*
	 * @brief	open database
	 */
	virtual bool open(const char* location) { return false; };

	/*
	 * @brief close database
	 */
	virtual void close() = 0;

};


} /* namespace interface */
} /* namespace cossb */



#endif /* _COSSB_INTERFACE_IDATABASE_HPP_ */
