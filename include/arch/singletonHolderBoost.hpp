
/*
@FILE	singletonHolderBoost.hpp
@BRIEF	singleton holder pattern architecture class with boost library
*/

#ifndef __COMMON_ARCH_SINGLETONHOLDER_BOOST__
#define __COMMON_ARCH_SINGLETONHOLDER_BOOST__

#include <iostream>
#include <utility>
#include <boost\core\noncopyable.hpp>
#include <boost\thread\once.hpp>
#include <boost\scoped_ptr.hpp>

using namespace std;

namespace dgist {
	namespace arch {

		template<class T> class singletonHolderBoost : private boost::noncopyable
		{
		public:
			static T* instance(){
				boost::call_once(&createInstance, _once);
				return _instance.get();
			}

		protected:
			singletonHolderBoost() { }
			static void createInstance() { _instance.reset(new T()); }

		private:
			static boost::once_flag _once;
			static boost::scoped_ptr<T> _instance;
			};

			template<class T> boost::once_flag singletonHolderBoost<T>::_once = BOOST_ONCE_INIT;
			template<class T> boost::scoped_ptr<T> singletonHolderBoost<T>::_instance;


	} /* namespace arch */
} /* namespace dgist */


#endif
