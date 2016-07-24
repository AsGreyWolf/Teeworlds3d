
# Uncomment this if you're using STL in your project
# See CPLUSPLUS-SUPPORT.html in the NDK documentation for more information
# APP_STL := stlport_static

APP_ABI := arm64-v8a #armeabi armeabi-v7a x86 x86_64 mips mips64
APP_CPPFLAGS += -std=c++11 -O3
APP_STL := gnustl_shared
