

#ifndef __FILE_COLLECTOR__
#define	__FILE_COLLECTOR__

#include <vector>
#include <string>

using namespace std;

namespace cossb {
	namespace file {

		class collector {
		public:

			typedef struct _path {
				string absolute;
				string relative;
				string filename;
				string ext;
			} filepath;

			collector(const char* path, const char* ext);
			virtual ~collector();

			/*
			@brief	update files in the path
			@return	number of files
			*/
			int update();

			/*
			@return	file container
			*/
			vector<filepath>& getList() { return _file_container; }

			/*
			@brief	return true if exist
			*/
			bool exist(const char* filename);

			/*
			@brief	remove elements
			*/
			void remove(const char* filename);

			/*
			@brief	number of collected files
			*/
			int size() { return (int)_file_container.size(); }

			/*
			@brief	return path
			*/
			filepath getPath(const char* filename) {
				filepath tmp;
				for (auto& file : _file_container) {
					if (file.filename == filename) {
						tmp = file;
						break;
					}
				}
				return tmp;
			}


			void ordering();

		private:
			void _update(const char* path, const char* ext);

		private:
			string _path;
			string _ext;
			vector<filepath> _file_container;

			//order
			vector<pair<int, int>> _order_index;	//stem, index

		};
	}
}


#endif
