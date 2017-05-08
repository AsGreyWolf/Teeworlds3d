LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../../../other/sdl/include
SDL_GLM_PATH := ../../../other/glm

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
	$(LOCAL_PATH)/$(SDL_GLM_PATH) \
	$(LOCAL_PATH)

# Add your application source files here...
LOCAL_SRC_FILES := ../SDL/src/main/android/SDL_android_main.c \
$(wildcard *.cpp) \
$(wildcard **/*.cpp) \
$(wildcard **/**/*.cpp) \
$(wildcard **/**/**/*.cpp) \
$(wildcard **/**/**/**/*.cpp) \
$(wildcard **/**/**/**/**/*.cpp)

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf SDL2_image

LOCAL_LDLIBS := -lGLESv3 -llog

include $(BUILD_SHARED_LIBRARY)
