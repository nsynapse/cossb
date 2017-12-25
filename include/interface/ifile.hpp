/**
 * @file		ifile.hpp
 * @brief		file interface
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2017. 12
 * @details		file interface
 */


#ifndef _COSSB_IFILE_HPP_
#define _COSSB_IFILE_HPP_

namespace cossb {
namespace interface {

class ifile {

public:
	ifile() { }
	virtual ~ifile() { }

	/**
	 * @brief	open interface
	 */
	virtual bool open(const char* filepath){
		return false;
	}

	/**
	 * @brief	close interface
	 */
	virtual void close(){

	}

	/**
	 * @brief	read interface
	 */
	virtual bool read(const char* filepath) {
		return false;
	}

	/**
	 * @brief	write interface
	 */
	virtual void write(const char* filepath){

	}


private:

};

} /* namespace interface */
} /* namespace cossb */

#endif
