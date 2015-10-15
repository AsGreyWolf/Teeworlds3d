#include "System.h"

#include <ctime>
#include "../../other/sdl/include/SDL.h"
#include "../../other/sdl/include/SDL_thread.h"
#include "Console.h"
#include "World.h"
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

class System* pSystem;
System* g_System(){ return pSystem; }

const int System::MAX_FILENAME = FILENAME_MAX;
int System::frames = 0;

int calcFPS(void *param){
	SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);
	SDL_Delay(1000);
	while (pSystem){
		Console::Info("FPS = " + to_string(System::frames));
		pSystem->fps = System::frames == 0 ? 60 : System::frames;
		System::frames = 0;
		SDL_Delay(1000);
	}
	return 0;
}

SDL_Thread *fpsThread;
SDL_Thread *asyncThread;
System::System(){
	srand(time(NULL));
	PATH_CUR = string(SDL_GetBasePath());
	PATH_DATA = PATH_CUR + "data/";
	pSystem = this;
	fps = 60;
	tickCoeff = 1.0f / fps;
	lasttickTime = g_System()->GetTime();
	if (SDL_Init(SDL_INIT_TIMER) != 0)
	{
		Console::Err("Unable to initialize SDL timer: " + string(SDL_GetError()));
		return; //TODO: need exceptions
	}
	SDL_version ver;
	SDL_GetVersion(&ver);
	Console::Info("Initialized SDL " + to_string(ver.major) + "." + to_string(ver.minor) + "." + to_string(ver.patch));
	fpsThread = SDL_CreateThread(calcFPS, "fpsThread", (void *)NULL);
	//asyncThread = SDL_CreateThread(async, "asyncThread", (void *)NULL);
};
System::~System(){
	pSystem = 0;
	int r;
	SDL_WaitThread(asyncThread, &r);
	SDL_WaitThread(fpsThread, &r);
};
void System::Tick(){
	long tickTime = g_System()->GetTime();
	tickCoeff = (tickTime - lasttickTime)*1.0 / 1000;
	lasttickTime = tickTime;
	frames++;
}
string System::GetPath(){
	return PATH_CUR;
};
string System::GetDataFile(string str){
	return PATH_DATA + str;
}
long System::GetTime(){
	return SDL_GetTicks();
};
void System::GetFilesInDirectory(std::vector<std::string> &out, const std::string &directory)
{
#ifdef WIN32
	HANDLE dir;
	WIN32_FIND_DATAW file_data;
	char str[MAX_FILENAME];
	strcpy(str, (directory + "/*").c_str());
	LPWSTR wstr = (LPWSTR)malloc(MAX_FILENAME*sizeof(WCHAR));
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, wstr, MAX_FILENAME);
	if ((dir = FindFirstFileW(wstr, &file_data)) == INVALID_HANDLE_VALUE)
		return;
	do {
		const std::wstring wfile_name = file_data.cFileName;
		std::string file_name = std::string(wfile_name.begin(), wfile_name.end());
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
	if ((dp = opendir(directory.c_str())) == NULL) {
		return;
	}

	while ((dirp = readdir(dp)) != NULL) {
		if (dirp->d_type != DT_DIR)
			out.push_back(string(dirp->d_name));
	}
	closedir(dp);
	return;
#endif
};

#ifdef WIN32
#ifdef VS15
FILE* stdfiles= new FILE[3]{ *stdin, *stdout, *stderr };
extern "C" FILE* __iob_func() {
	return stdfiles;
}
#endif
#endif