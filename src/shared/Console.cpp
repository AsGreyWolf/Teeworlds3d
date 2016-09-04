#include "Console.h"

#include <iostream>
#ifdef __ANDROID__
#include <android/log.h>
#define LOG_TAG "Teeworlds3d"
#endif

class Console *pConsole;
Console *g_Console() { return pConsole ? pConsole : new Console(); }

Console::Console() : SharedComponent() { pConsole = this; };
Console::~Console() { pConsole = 0; };
void Console::Err(const std::string &c) {
	std::cerr << "[ERROR] " << c << std::endl;
#ifdef __ANDROID__
	__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[ERROR] %s", c.c_str());
#endif
};
void Console::Info(const std::string &c) {
	std::cout << "[INFO] " << c << std::endl;
#ifdef __ANDROID__
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "[INFO] %s", c.c_str());
#endif
};
