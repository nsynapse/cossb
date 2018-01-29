
/*
@FILE	singletonHolder.hpp
@BRIEF	singleton holder pattern architecture class
*/

#ifndef __COMMON_ARCH_SINGLETONHOLDER__
#define __COMMON_ARCH_SINGLETONHOLDER__

#include <iostream>
#include <utility>

using namespace std;

namespace dgist {
	namespace arch {

		template<class _T>
		class singletonHolder {
		public:
			template<typename... Args>
			static _T* instance(Args... args){
				if(!_instance)
					_instance = new _T(std::forward<Args>(args)...);
				return _instance;
			}

			static void destory() {
				if(_instance) {
					delete _instance;
					_instance = nullptr;
				}
			}

		protected:
			singletonHolder() { }
			singletonHolder(singletonHolder const&) { }
			singletonHolder& operator=(singletonHolder const&) { return *this; }

		private:
			static _T* _instance;
		};

		template <class _T> _T* singletonHolder<_T>::_instance = nullptr;

	} /* namespace arch */
} /* namespace dgist */

#endif
