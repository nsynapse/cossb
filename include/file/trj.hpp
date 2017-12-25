

#ifndef _COSSB_FILE_TRJ_HPP_
#define _COSSB_FILE_TRJ_HPP_

#include <interface/ifile.hpp>

namespace cossb  {
namespace file {

class trj : public interface::ifile {
	trj();
	virtual ~trj();

	bool open(const char* filepath);
	void close();

};
} /* namespace file */
} /* namespace cossb */


#endif /* _COSSB_FILE_TRJ_HPP_ */
