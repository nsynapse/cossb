/**
 * @file		sha1.hpp
 * @brief		Secure Hash Standard 1 Algorithm (Employed public code into the COSSB)
 * @author		Steve Reid (Original C Code)
 * 				Bruce Guenter (Small changes to fit into bglibs)
 * 				Volker Grabsch (Translation to simpler C++ Code)
 * 				Eugene Hopkinson (Safety improvements)
 * @date 		2015. 8. 2
 * @details	apply hash algorithm for Service Component download and Message transfer.
 * 				This code was cloned from Github(https://github.com/vog/sha1)
 *
 */

#ifndef _COSSB_UTIL_SHA1_HPP_
#define _COSSB_UTIL_SHA1_HPP_

namespace cossb {
namespace algorithm {

#include <string>


class sha1
{
public:
    sha1();
    void update(const std::string &s);
    void update(std::istream &is);
    std::string final();
    static std::string from_file(const std::string &filename);

private:
    unsigned int digest[5];
    std::string buffer;
    unsigned long int transforms;
};

} /* namespace algorithm */
} /* namespace cossb */

#endif /* _COSSB_UTIL_SHA1_HPP_ */
