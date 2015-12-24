
#include "pid.h"
#include <dirent.h>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

namespace cossb {
namespace util {

int get_pid(const char* processname)
{
	int pid = -1;

	DIR* path = opendir("/proc");
	if(path!=nullptr)
	{
		struct dirent* dir;
		while(pid<0 && (dir=readdir(path)))
		{
			int id = atoi(dir->d_name);
			if(id>0)
			{
				string cmdpath = string("/proc/")+dir->d_name+"/cmdline";
				ifstream cmdfile(cmdpath.c_str());
				string cmdline;
				getline(cmdfile, cmdline);
				if(!cmdline.empty())
				{
					size_t pos = cmdline.find('\0');
					if(pos!=string::npos)
						cmdline = cmdline.substr(0, pos);
					pos = cmdline.rfind('/');
					if(pos!=string::npos)
						cmdline = cmdline.substr(pos+1);
					if(processname == cmdline)
						pid = id;
				}
			}

		}
	}

	closedir(path);
	return pid;
}

} /* namespace base */
} /* namespace cossb */
