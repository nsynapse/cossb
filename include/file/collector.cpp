#include "collector.hpp"
#include <cossb.hpp>
#include <boost/filesystem.hpp>
#include <base/log.hpp>

namespace cossb {
	namespace file {

		collector::collector(const char* path, const char* ext):_path(path), _ext(ext) {
			this->_update(path, ext);
		}

		collector::~collector() {
			_file_container.clear();
		}

		bool collector::exist(const char* filename) {
			bool exist = false;
			for(auto& file : _file_container) {
				if(!file.filename.compare(filename)) {
					exist = true;
					break;
				}
			}
			return exist;
		}

		void collector::remove(const char* filename)
		{
			vector<filepath>::iterator itr;
			for(itr=_file_container.begin(); itr != _file_container.end(); itr++) {
				if(!itr->filename.compare(filename)) {
					_file_container.erase(itr);
					break;
				}
			}
		}


		void collector::ordering() {
			//if(!_file_container.empty()) {
			//	//index ordering
			//	std::sort(_order_index.begin(), _order_index.end());
			//	vector<string> _tmp_container;

			//	for(auto& index : _order_index) {
			//		_tmp_container.push_back(_file_container[index.second]);
			//	}

			//	_file_container.clear();
			//	_file_container = std::move(_tmp_container);
			//
			//}
		}

		void collector::_update(const char* path, const char* ext) {
			namespace fs = boost::filesystem;
			fs::path root_ext(path);

			if(!fs::exists(root_ext) || !fs::is_directory(root_ext)) {
				cossb_log->log(log::loglevel::INFO, fmt::format("Could not find files in {}", root_ext.string()));
			}
			else {
				fs::recursive_directory_iterator ext_itr(root_ext);
				fs::recursive_directory_iterator ext_enditr;

				int index = 0;
				while(ext_itr != ext_enditr) {
					if(!fs::is_directory(*ext_itr))
					{
						if(fs::is_regular_file(*ext_itr) && (ext_itr->path().extension() == _ext.c_str()))
						{

							filepath path;
							path.ext = ext_itr->path().extension().string();
							path.relative = ext_itr->path().string();
							path.filename = ext_itr->path().filename().stem().string();
							path.absolute = boost::filesystem::absolute(ext_itr->path().filename()).string();
							_file_container.push_back(path);
						}
					}
					++ext_itr;
				}
			}
		}

		int collector::update() {
			_file_container.clear();
			this->_update(_path.c_str(), _ext.c_str());
			return (int)_file_container.size();
		}
	}
}
