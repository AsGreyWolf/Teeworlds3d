#include "System.h"

#include <ctime>
#ifdef WIN32
#include <codecvt>
#include <Windows.h>
#include <direct.h>
#define GetCurrentDir(a, b) GetCurrentDirectory(b, a)
#else
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/time.h>
#define GetCurrentDir(a, b) getcwd(a, b)
#endif
#include <SDL.h>
#include <SDL_thread.h>
#include <shared/Console.h>

class System *pSystem;
System *g_System() { return pSystem ? pSystem : new System(); }

int frames = 0;
int calcFPS(void *param) {
	SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);
	SDL_Delay(1000);
	while (pSystem) {
		g_Console()->Info("FPS = " + std::to_string(frames));
		pSystem->fps = frames == 0 ? 60 : frames;
		frames = 0;
		SDL_Delay(1000);
	}
	return 0;
}
SDL_Thread *fpsThread;
System::System() : SharedComponent() {
	srand(time(NULL));
	PATH_CUR = std::string(SDL_GetBasePath());
	PATH_DATA = PATH_CUR + "data/";
	pSystem = this;
	fps = 60;
	tickCoeff = 1.0f / fps;
	lasttickTime = g_System()->GetTime();
	if (SDL_Init(SDL_INIT_TIMER) != 0) {
		g_Console()->Err("Unable to initialize SDL Timer: " +
		                 std::string(SDL_GetError()));
		return; // TODO: need exceptions
	}
	SDL_version ver;
	SDL_GetVersion(&ver);
	g_Console()->Info("Initialized SDL Timer " + std::to_string(ver.major) + "." +
	                  std::to_string(ver.minor) + "." + std::to_string(ver.patch));
	fpsThread = SDL_CreateThread(calcFPS, "fpsThread", (void *)NULL);
};
System::~System() {
	pSystem = 0;
	int r;
	SDL_WaitThread(fpsThread, &r);
	SDL_QuitSubSystem(SDL_INIT_TIMER);
};
void System::Tick() {
	SharedComponent::Tick();
	long tickTime = g_System()->GetTime();
	tickCoeff = (tickTime - lasttickTime) * 1.0 / 1000;
	if (tickCoeff > 1)
		tickCoeff = 1.0f / 60;
	lasttickTime = tickTime;
	frames++;
}
std::string System::GetPath() const { return PATH_CUR; };
std::string System::GetDataFile(const std::string &str) const {
	return PATH_DATA + str;
}
long System::GetTime() const { return SDL_GetTicks(); };
void System::GetFilesInDirectory(std::vector<std::string> &out,
                                 const std::string &directory) const {
#ifdef WIN32
	HANDLE dir;
	WIN32_FIND_DATAW file_data;
	char str[FILENAME_MAX];
	str[0] = 0;
	strcpy(str, (directory + "/*").c_str());
	LPWSTR wstr = (LPWSTR) new WCHAR(FILENAME_MAX);
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, wstr, FILENAME_MAX);
	if ((dir = FindFirstFileW(wstr, &file_data)) == INVALID_HANDLE_VALUE)
		return;
	do {
		const std::wstring wfile_name = file_data.cFileName;
		std::string file_name = std::string(wfile_name.begin(), wfile_name.end());
		const bool is_directory =
		    (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
		if (file_name[0] == '.')
			continue;
		if (is_directory)
			continue;
		out.push_back(file_name);
	} while (FindNextFileW(dir, &file_data));
	delete[](WCHAR *)wstr;
	FindClose(dir);
#else
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(directory.c_str())) == NULL) {
		return;
	}

	while ((dirp = readdir(dp)) != NULL) {
		if (dirp->d_name[0] == '.')
			continue;
		if (dirp->d_type != DT_DIR)
			out.push_back(std::string(dirp->d_name));
	}
	closedir(dp);
	return;
#endif
};

#ifdef WIN32
#ifdef VS15
FILE *stdfiles = new FILE[3]{*stdin, *stdout, *stderr};
extern "C" FILE *__iob_func() { return stdfiles; };
#endif
#endif
