#include "system.h"

#include <SDL.h>
#include <atomic>
#include <chrono>
#include <shared/console.h>
#include <thread>
#ifdef WIN32
#include <Windows.h>
#include <codecvt>
#include <cstdlib>
#include <direct.h>
#define current_dir(a, b) GetCurrentDirectory(b, a)
#else
#include <dirent.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#define current_dir(a, b) getcwd(a, b)
#endif

using namespace std;
using namespace tee3d;
using namespace tee3d::shared;

static performance_t<60> perf;
static string PATH_CUR;
static string PATH_DATA;
system_component::system_component() : component() {
#ifdef __ANDROID__
	PATH_CUR = "/sdcard/Android/data/tee3d/"; // TODO: package name && unpack
#else
	PATH_CUR = string(SDL_GetBasePath());
#endif
	PATH_DATA = PATH_CUR + "data/";
};
system_component::~system_component(){};
void system_component::tick() {
	component::tick();
	perf = sync<system_component, 60>("SYSTEM");
}

string system_component::path() const { return PATH_CUR; };
string system_component::data_file(const string &str) const {
	return PATH_DATA + str;
}
vector<string>
system_component::files_in_directory(const string &directory) const {
	vector<string> out;
#ifdef WIN32
	HANDLE dir;
	WIN32_FIND_DATAW file_data;
	char str[FILENAME_MAX];
	str[0] = 0;
	strcpy(str, (directory + "/*").c_str());
	LPWSTR wstr = (LPWSTR)malloc(FILENAME_MAX * sizeof(WCHAR));
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, wstr, FILENAME_MAX);
	if ((dir = FindFirstFileW(wstr, &file_data)) == INVALID_HANDLE_VALUE)
		return;
	do {
		const wstring wfile_name = file_data.cFileName;
		string file_name = string(wfile_name.begin(), wfile_name.end());
		const bool is_directory =
		    (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
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
	if ((dp = opendir(directory.c_str())) == nullptr) {
		return out;
	}

	while ((dirp = readdir(dp)) != nullptr) {
		if (dirp->d_name[0] == '.') {
			continue;
		}
		if (dirp->d_type != DT_DIR) {
			out.push_back(string(dirp->d_name));
		}
	}
	closedir(dp);
#endif
	return out;
};

duration_t system_component::time() const {
	using chrono::high_resolution_clock;
	using chrono::duration_cast;
	return duration_cast<chrono::microseconds>(
	    high_resolution_clock::now().time_since_epoch());
};
template <class T, int FPS>
performance_t<FPS> system_component::sync(const string &tag) const {
	static duration_t prev = time();
	duration_t cur = time();
	this_thread::sleep_for(duration_cast<duration_t>(seconds(1)) / FPS -
	                       (cur - prev));
	performance_t<FPS> result(prev, cur);
	console()->info("[" + tag + "]FPS=" + to_string(result.dynamic_fps));
	swap(prev, cur);
	return result;
}
int system_component::fps() const { return perf.dynamic_fps; }
double system_component::tick_factor() const { return perf.factor; }

#ifdef WIN32
#ifdef VS15
FILE *stdfiles = new FILE[3]{*stdin, *stdout, *stderr};
extern "C" FILE *__iob_func() { return stdfiles; };
#endif
#endif
