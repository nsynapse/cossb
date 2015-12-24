/*
 * service.hpp
 *
 *  Created on: 2015. 10. 13.
 *      Author: hwang
 */

#ifndef INCLUDE_SERVICE_HPP_
#define INCLUDE_SERVICE_HPP_

#include "interface/iservice.hpp"

namespace cossb {

class service : public interface::iservice {
public:
	service();
	virtual ~service();
};

} /* namespace cossb */

#endif /* INCLUDE_SERVICE_HPP_ */
