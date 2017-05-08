#include "console.h"

#include <iostream>
#include <sstream>
#ifdef __ANDROID__
#include <android/log.h>
#define LOG_TAG "Teeworlds3d"
#endif

using namespace tee3d::shared;
using namespace std;

console_component::console_component() : component(){};
console_component::~console_component(){};
template <class T> void console_component::err(T &&c) {
	cerr << "[ERROR] " << c << endl;
#ifdef __ANDROID__
	ostringstream ss;
	ss << c;
	__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[ERROR] %s",
	                    ss.str().c_str());
#endif
};
template <class T> void console_component::info(T &&c) {
	cout << "[INFO] " << c << endl;
#ifdef __ANDROID__
	ostringstream ss;
	ss << c;
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "[INFO] %s", ss.str().c_str());
#endif
};
