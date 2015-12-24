/*
 * uuid.hpp
 *
 *  Created on: 2015. 10. 13.
 *      Author: hwang
 */

#ifndef INCLUDE_UTIL_UUID_HPP_
#define INCLUDE_UTIL_UUID_HPP_

#include <uuid/uuid.h>
#include <string>

using namespace std;

namespace cossb {
namespace util {

typedef struct _uuid {
public:
	unsigned char code[16];

	void _uuid() {
		uuid_generate(code);
		memset(encoded, 0x00, sizeof(encoded));
		uuid_unparse(code, encoded);
	}

	const char* str() { return (const char*)encoded; }

private:
	char encoded[64];
} uuid;

} /* namespace util */
} /* namespace cossb */



#endif /* INCLUDE_UTIL_UUID_HPP_ */
