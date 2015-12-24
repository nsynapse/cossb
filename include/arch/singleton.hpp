/**
 * @file		singleton.hpp
 * @brief		dynamic Singleton pattern design template class
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 2
 * @details	singleton 패턴 템플릿 클래스
 */

#ifndef _COSSB_ARCH_SINGLETON_HPP_
#define _COSSB_ARCH_SINGLETON_HPP_

#include <iostream>
#include <utility>

using namespace std;

namespace cossb {
namespace arch {

/**
 * @brief	dynamic singleton design pattern
 */
template <class T>
class singleton {
public:
	template<typename... Args>
	static T* instance(Args... args) {
		if(!_instance) {
			_instance = new T(std::forward<Args>(args)...);
		}
		return _instance;
	}
	static void destroy() {
		if(_instance) {
			delete _instance;
			_instance = nullptr;
		}
	}

protected:
	singleton() {}
	singleton(singleton const&) {}
	singleton& operator=(singleton const&) { return *this; }


private:
	static T* _instance;

};

template <class T> T* singleton<T>::_instance = nullptr;

} /* namespace arch */
} /* namespace cossb */


#endif /* _COSSB_ARCH_SINGLETON_HPP_ */
