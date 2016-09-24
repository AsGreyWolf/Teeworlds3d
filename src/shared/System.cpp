#include "System.h"

#include <SDL.h>
#include <SDL_thread.h>
#include <ctime>
#include <mutex>
#include <shared/Console.h>
#ifdef WIN32
#include <Windows.h>
#include <codecvt>
#include <cstdlib>
#include <direct.h>
#define GetCurrentDir(a, b) GetCurrentDirectory(b, a)
#else
#include <dirent.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#define GetCurrentDir(a, b) getcwd(a, b)
#endif

class System *pSystem;
System *g_System() { return pSystem ? pSystem : new System(); }

Mutex System::mutex;
static int frames = 0;
static long lastTickTime;
static DelayedThread *fpsThread;
System::System() : SharedComponent() {
	srand(time(NULL));
#ifdef __ANDROID__
	PATH_CUR = "/sdcard/Android/data/tee3d/"; // TODO: package name && unpack
#else
	PATH_CUR = std::string(SDL_GetBasePath());
#endif
	PATH_DATA = PATH_CUR + "data/";
	pSystem = this;
	fps = 60;
	tickCoeff = 1.0f / fps;
	lastTickTime = g_System()->GetTime();
	if (SDL_Init(SDL_INIT_TIMER) != 0) {
		g_Console()->Err("Unable to initialize SDL Timer: " +
		                 std::string(SDL_GetError()));
		return; // TODO: need exceptions
	}
	SDL_version ver;
	SDL_GetVersion(&ver);
	g_Console()->Info("Initialized SDL Timer " + std::to_string(ver.major) + "." +
	                  std::to_string(ver.minor) + "." + std::to_string(ver.patch));
	fpsThread = new DelayedThread(
	    [&]() {
		    g_Console()->Info("FPS = " + std::to_string(frames));
		    pSystem->fps = frames;
		    frames = 0;
		   },
	    1000);
	fpsThread->Start();
};
System::~System() {
	std::unique_lock<Mutex>(mutex);
	delete fpsThread;
	pSystem = 0;
	SDL_QuitSubSystem(SDL_INIT_TIMER);
};
void System::Tick() {
	SharedComponent::Tick();
	long tickTime = g_System()->GetTime();
	tickCoeff = (tickTime - lastTickTime) * 1.0 / 1000;
	if (tickCoeff > 1)
		tickCoeff = 1.0f;
	lastTickTime = tickTime;
	frames++;
}
std::string System::GetPath() const { return PATH_CUR; };
std::string System::GetDataFile(const std::string &str) const {
	return PATH_DATA + str;
}
long System::GetTime() const { return SDL_GetTicks(); };
std::vector<std::string>
System::GetFilesInDirectory(const std::string &directory) const {
	std::vector<std::string> out;
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
	free(wstr);
	FindClose(dir);
#else
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(directory.c_str())) == NULL) {
		return out;
	}

	while ((dirp = readdir(dp)) != NULL) {
		if (dirp->d_name[0] == '.')
			continue;
		if (dirp->d_type != DT_DIR)
			out.push_back(std::string(dirp->d_name));
	}
	closedir(dp);
#endif
	return out;
};

int ThreadRunner(void *t) {
	DelayedThread *thread = (DelayedThread *)t;
	int time = 0;
	while (true) {
		int delay = 0;
		{
			std::unique_lock<Mutex>(thread->m);
			if (!thread->d) {
				return 0;
			}
			delay = thread->d;
		}
		thread->f();
		{
			std::unique_lock<Mutex>(System::mutex);
			if (!pSystem) {
				return 0;
			}
			int newTime = pSystem->GetTime();
			SDL_Delay(std::max(delay - (newTime - time), 0));
			time += delay;
		}
	}
}
DelayedThread::DelayedThread(const std::function<void()> &func, long delay)
    : f(func), d(delay) {}
DelayedThread::~DelayedThread() { Stop(); }
void DelayedThread::Start() {
	t = SDL_CreateThread(
	    ThreadRunner,
	    (std::string("ThreadRunner") + std::to_string((size_t)(void *)&f)).c_str(),
	    (void *)this);
}
void DelayedThread::Stop() {
	{
		std::unique_lock<Mutex>(m);
		d = 0;
	}
	int r;
	if (t)
		SDL_WaitThread(t, &r);
	t = NULL;
}

Mutex::Mutex() { m = SDL_CreateMutex(); }
Mutex::~Mutex() { SDL_DestroyMutex(m); }
Mutex::Mutex(Mutex &&second) noexcept { m = second.m; }
Mutex &&Mutex::operator=(Mutex &&second) noexcept {
	m = second.m;
	return std::move(*this);
}
void Mutex::lock() { SDL_LockMutex(m); }
bool Mutex::try_lock() { return SDL_TryLockMutex(m) == 0; }
void Mutex::unlock() { SDL_UnlockMutex(m); }
Mutex::native_handle_type Mutex::native_handle() { return m; }

#ifdef WIN32
#ifdef VS15
FILE *stdfiles = new FILE[3]{*stdin, *stdout, *stderr};
extern "C" FILE *__iob_func() { return stdfiles; };
#endif
#endif
