/**
 * @file		icomm.hpp
 * @brief		communication interface class
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 2
 * @details		communication base interface class
 */

#ifndef _COSSB_INTERFACE_ICOMM_HPP_
#define _COSSB_INTERFACE_ICOMM_HPP_

namespace cossb {
namespace interface {

/**
 * @brief	communication read interface
 */
class icommread {
public:
	virtual ~icommread() {}
	virtual int read() const = 0;
};

/**
 * @brief	communication write interface
 */
class icommwrite {
public:
	virtual ~icommwrite() {}
	virtual int write(const char* data, int len) = 0;
};

/**
 * @vrief	communication interface
 */
class icomm : public icommread, public icommwrite {
public:
	icomm() { }
	virtual ~icomm() { }

	virtual int read() const = 0;
	virtual int write(const char* data, int len) = 0;

};

} /* namespace interface */
} /* namespace cossb */



#endif /* _COSSB_INTERFACE_ICOMM_HPP_ */
