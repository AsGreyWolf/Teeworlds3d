#ifndef SYSTEM_H
#define SYSTEM_H

#include "SharedComponent.h"

#include <functional>
#include <string>
#include <vector>

int ThreadRunner(void *param);

class Mutex {
	class SDL_mutex *m;

public:
	using native_handle_type = SDL_mutex *;

	Mutex();
	Mutex(const Mutex &second) = delete;
	Mutex(Mutex &&second) noexcept;
	~Mutex();

	Mutex &operator=(const Mutex &second) = delete;
	Mutex &&operator=(Mutex &&second) noexcept;

	void lock();
	bool try_lock();
	void unlock();
	native_handle_type native_handle();
};

class DelayedThread {
	class SDL_Thread *t;
	std::function<void()> f;
	Mutex m;
	long d;
	friend int ThreadRunner(void *param);

public:
	DelayedThread(const std::function<void()> &func, long delay);
	~DelayedThread();

	void Start();
	void Stop();
};

///<summary>Interaction with OS</summary>
class System : public SharedComponent {
private:
	System();
	friend System *g_System();
	friend int ThreadRunner(void *param);

public:
	~System() override;

	///<summary>Tick the component(graphics thread)</summary>
	void Tick() override;

	///<summary>Returns app directory path</summary>
	std::string GetPath() const;
	///<summary>Returns time in ms</summary>
	long GetTime() const;
	///<summary>Fills out with filenames in the directory</summary>
	std::vector<std::string>
	GetFilesInDirectory(const std::string &directory) const;
	///<summary>Returns filename in data folder</summary>
	///<param name="str">Filename</param>
	std::string GetDataFile(const std::string &str) const;

	int fps;
	double tickCoeff;

private:
	std::string PATH_CUR;
	std::string PATH_DATA;
	static Mutex mutex;
};
System *g_System();

#endif
