
/*
@FILE	singletonSafe.hpp
@BRIEF	singleton pattern class using C++11 acquire and release fences(Double checked locking)
*/

#ifndef __COMMON_ARCH_SINGLETON_SAFE__
#define __COMMON_ARCH_SINGLETON_SAFE__

#include <iostream>
#include <utility>
#include <atomic>
#include <mutex>

using namespace std;

namespace dgist {
	namespace arch {

		template<class _T> class singletonSafe {
		public:
			template<typename... Args>
			static _T* instance(Args... args){

				singletonSafe* ptr = _instance.load(std::memory_order_relaxed);
				std::_Atomic_thread_fence(std::memory_order_acquire);
				if(!ptr){
					std::lock_guard<std::mutex> lock(_mutex);
					ptr = _instance.load(std::memory_order_relaxed);
					if(!ptr){
						ptr = new _T(std::forward<Args>(args)...);
						std::_Atomic_thread_fence(std::memory_order_release);
						_instance.store(ptr, std::memory_order_relaxed);
					}
				}
				return ptr;
			}

			static void destory() {
				if(_instance) {
					delete _instance;
					_instance = nullptr;
				}
			}

		protected:
			singletonSafe() { }
			singletonSafe(singletonSafe const&) { }
			singletonSafe& operator=(singletonSafe const&) { return *this; }

		private:
			static std::atomic<_T*> _instance;
			static std::mutex _mutex;
		};

		template <class _T> _T* singletonSafe<_T>::_instance = nullptr;

	} /* namespace arch */
} /* namespace dgist */

#endif


/*std::atomic<Singleton*> Singleton::m_instance;
std::mutex Singleton::m_mutex;

Singleton* Singleton::getInstance() {
Singleton* tmp = m_instance.load(std::memory_order_relaxed);
std::atomic_thread_fence(std::memory_order_acquire);
if(tmp == nullptr) {
std::lock_guard<std::mutex> lock(m_mutex);
tmp = m_instance.load(std::memory_order_relaxed);
if(tmp == nullptr) {
tmp = new Singleton;
std::atomic_thread_fence(std::memory_order_release);
m_instance.store(tmp, std::memory_order_relaxed);
}
}
return tmp;
}*/
