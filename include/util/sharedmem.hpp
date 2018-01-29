/**
* @file		sahredmemory.hpp
* @brief	shared memory based on boost library
* @author	Byunghun Hwang <bhhwang@dgist.ac.kr>
*/

#ifndef __UTIL_SHARED_MEMORY__
#define __UTIL_SHARED_MEMORY__


#include <boost\interprocess\shared_memory_object.hpp> //for shared memory
#include <boost\interprocess\mapped_region.hpp>
#include <boost\interprocess\managed_shared_memory.hpp>
#include <string>
#include <utils\log.hpp>

using namespace std;

namespace dgist {
	namespace utils {

		template <typename _T>
		class sharedmemory {
		public:

			sharedmemory(){ }
			sharedmemory(const char* object_name):_object_name(object_name){
				//clear it before create a shared memory object

			}

			virtual ~sharedmemory(){
				_object_name.clear();
				this->release();
			}

			/*
			@brief create new shared memory object and mapped region
			*/
			bool create() {
				if(_object_name.empty())
					return false;
				return this->create(_object_name.c_str());
			}

			bool create_readonly() {
				boost::interprocess::shared_memory_object::remove(_object_name.c_str());
				try {
					_object = new boost::interprocess::shared_memory_object(boost::interprocess::create_only, object_name, boost::interprocess::read_only);
					_object->truncate(sizeof(_T));
					_region = new boost::interprocess::mapped_region(*_object, boost::interprocess::read_only);
				}
				catch(boost::interprocess::interprocess_exception& e) {
					logger->log(dgist::abstract::iLog::loglevel::ERR, fmt::format("IPC Error : {}", e.what()));
					return false;
				}
				return true;
			}

			bool create(const char* object_name) {
				boost::interprocess::shared_memory_object::remove(_object_name.c_str());
				try {
					_object = new boost::interprocess::shared_memory_object(boost::interprocess::create_only, object_name, boost::interprocess::read_write);
					_object->truncate(sizeof(_T));
					_region = new boost::interprocess::mapped_region(*_object, boost::interprocess::read_write);
				}
				catch(boost::interprocess::interprocess_exception& e) {
					logger->log(dgist::abstract::iLog::loglevel::ERR, fmt::format("IPC Error : {}", e.what()));
					return false;
				}
				return true;
			}

			/*
			@brief	connect to the already created shared memory object
			*/
			bool connect_readonly(const char* object_name) {
				try {
					if(_region || _object)
						return false;

					_object = new boost::interprocess::shared_memory_object(boost::interprocess::open_only, object_name, boost::interprocess::read_only);
					_region = new boost::interprocess::mapped_region(*_object, boost::interprocess::read_only);
				}
				catch(boost::interprocess::interprocess_exception& e) {
					logger->log(dgist::abstract::iLog::loglevel::ERR, fmt::format("IPC Error : {}", e.what()));
					return false;
				}
				return true;
			}

			/*
			@brief	connect to the already created shared memory object
			*/
			bool connect_readwrite(const char* object_name) {
				try {
					if(_region || _object)
						return false;

					_object = new boost::interprocess::shared_memory_object(boost::interprocess::open_only, object_name, boost::interprocess::read_write);
					_region = new boost::interprocess::mapped_region(*_object, boost::interprocess::read_write);
				}
				catch(boost::interprocess::interprocess_exception& e) {
					logger->log(dgist::abstract::iLog::loglevel::ERR, fmt::format("IPC Error : {}", e.what()));
					return false;
				}
				return true;
			}

			/*
			@brief	return address to access
			*/
			_T* getAddress() {
				return static_cast<_T*>(_region->get_address());
			}

			/*
			@brief	clear shared memory
			*/
			void release() {
				//erase a shared memory object from the system
				//boost::interprocess::shared_memory_object::remove(_object_name.c_str());

				if(_region) {
					delete _region;
					_region = nullptr;
				}

				if(_object) {
					//_object->remove(_object_name.c_str());
					delete _object;
					_object = nullptr;
				}
			}

		private:
			string _object_name;
			boost::interprocess::shared_memory_object* _object = nullptr;
			boost::interprocess::mapped_region* _region = nullptr;
		};

	} /* namespace utils */
} /* namespace dgist */


#endif
