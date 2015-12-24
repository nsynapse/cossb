/**
 * @file		libadopter.hpp
 * @brief		internal standard library adopter(loader)
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 19
 * @details	COSSB library adopter
 */

#ifndef _COSSB_LIBADOPTER_HPP_
#define _COSSB_LIBADOPTER_HPP_

#include <dlfcn.h>
#include <string>
#include <util/format.h>

using namespace std;

namespace cossb {
namespace base {

template<class T>
class libadopter {
public:
	libadopter(const char* path) {
		_handle = dlopen(path, RTLD_NOW|RTLD_GLOBAL);
		if(_handle) {
			typedef T* create_t(void);
			create_t* pfcreate = (create_t*)dlsym(_handle, "create");
			if(pfcreate)
				_lib = pfcreate();
		}
	}

	virtual ~libadopter() {
		if(_lib) {
			typedef void(destroy_t)(T* arg);
			destroy_t* pfdestroy = (destroy_t*)dlsym(_handle, "destroy");
			if(pfdestroy)
				pfdestroy(_lib);
			_lib = nullptr;
		}

		if(_handle) {
			dlclose(_handle);
			_handle = nullptr;
		}
	}

	T* get_lib() { return _lib; }

private:
	void* _handle = nullptr;

	T* _lib = nullptr;
};

} /* namespace base */
} /* namespace cossb */


#endif /* _COSSB_LIBADOPTER_HPP_ */
