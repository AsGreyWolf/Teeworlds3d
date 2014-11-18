#ifndef SYSTEM_H
#define SYSTEM_H
#include <stdio.h>
#include <ctime>
#include <locale>
#ifdef WIN32
#include <codecvt>
#include <Windows.h>
#include <direct.h>
#define GetCurrentDir(a,b) GetCurrentDirectory(b,a)
#else
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/time.h>
#define GetCurrentDir(a,b) getcwd(a,b)
#endif
class System{
public:
	static const int MAX_FILENAME=FILENAME_MAX;
	static void Init(){
		srand(time(NULL));
	};
	static void GetPath(string &path){
		char pp[MAX_FILENAME];
		GetCurrentDir(pp,MAX_FILENAME);
		path=pp;
	};
	static long GetTime(){
		/*
		#ifdef WIN32
		//SYSTEMTIME time;
		//GetSystemTime(&time);
		return clock()*1000.0f/CLOCKS_PER_SEC;
		#else
		timeval curTime;
		gettimeofday(&curTime, NULL);
		return 1000 * curTime.tv_sec+curTime.tv_usec/1000;
		#endif
		*/
		return clock()*1000.0f/CLOCKS_PER_SEC;
	};
	static void GetFilesInDirectory(std::vector<std::string> &out, const std::string &directory)
	{
#ifdef WIN32
		HANDLE dir;
		WIN32_FIND_DATAW file_data;
		char str[MAX_FILENAME];
		strcpy(str,(directory+"/*").c_str());
		LPWSTR wstr = (LPWSTR)malloc(MAX_FILENAME*sizeof(WCHAR));
		MultiByteToWideChar(CP_ACP, 0, str, strlen(str)+1, wstr, MAX_FILENAME);
		if ((dir = FindFirstFileW(wstr, &file_data)) == INVALID_HANDLE_VALUE)
			return;
		do {
			const std::wstring wfile_name = file_data.cFileName;
			std::string file_name=std::string(wfile_name.begin(), wfile_name.end());
			const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
			if (file_name[0] == '.')
				continue;
			if (is_directory)
				continue;
			out.push_back(file_name);
		} while (FindNextFileW(dir, &file_data));
		free(wstr);
		FindClose(dir);
#else
		DIR *dp;
		struct dirent *dirp;
		if((dp  = opendir(directory.c_str())) == NULL) {
			return;
		}

		while ((dirp = readdir(dp)) != NULL) {
			if(dirp->d_type != DT_DIR)
				out.push_back(string(dirp->d_name));
		}
		closedir(dp);
		return;
#endif
	};
};
#endif
