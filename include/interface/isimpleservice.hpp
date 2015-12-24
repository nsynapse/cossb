/**
 * @file		isimpleservice.hpp
 * @brief		simple service interface
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 21
 * @details	simple service interface class
 */

#ifndef _COSSB_INTERFACE_ISIMPLESERVICE_HPP_
#define _COSSB_INTERFACE_ISIMPLESERVICE_HPP_


namespace cossb {
namespace interface {

class isimpleservice {
public:
	isimpleservice() { }
	virtual ~isimpleservice() { }

	/**
	 * @brief	service start interface function
	 */
	virtual void start() = 0;

	/**
	 * @brief	service stop interface function
	 */
	virtual void stop() = 0;

};

} /* namespace interface */
} /* namespace cossb */


#endif /* _COSSB_INTERFACE_ISIMPLESERVICE_HPP_ */
