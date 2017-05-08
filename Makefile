.PHONY: all clean client shared android android_apk android_data

CXX=g++
INC_DIR = -Isrc -Iother/sdl/include -Iother/glew/include -Iother/glm
CXXFLAGS=-c -Wall --std=c++1y -O3 -DLINUX -g -pg $(INC_DIR)
SRC_DIR = src
OBJ_DIR = objs
LIBS = -lGL -lGLEW -lSDL2 -lSDL2_image -lSDL2_ttf -lGLU

SRCS_SHARED = $(wildcard \
	$(SRC_DIR)/*.cpp \
	$(SRC_DIR)/shared/*.cpp \
	$(SRC_DIR)/shared/**/*.cpp \
	$(SRC_DIR)/shared/**/**/*.cpp \
)
OBJS_SHARED =  $(SRCS_SHARED:.cpp=.o)

SRCS_CLIENT = $(wildcard \
	$(SRC_DIR)/client/*.cpp \
	$(SRC_DIR)/client/**/*.cpp \
	$(SRC_DIR)/client/**/**/*.cpp \
	$(SRC_DIR)/client/**/**/**/*.cpp \
	$(SRC_DIR)/client/**/**/**/**/*.cpp \
)
OBJS_CLIENT = $(SRCS_CLIENT:.cpp=.o)
TARGET_CLIENT = teeworlds3d

TARGET_ANDROID_APK = SDLActivity-debug.apk
TARGET_ANDROID_DATA = AndroidData.zip

SRCS = $(wildcard $(SRCS_SHARED) $(SRCS_CLIENT))
OBJS = $(wildcard $(OBJS_SHARED) $(OBJS_CLIENT))
TARGET = $(TARGET_CLIENT) $(TARGET_ANDROID_APK) $(TARGET_ANDROID_DATA)

all: client android

client: $(TARGET_CLIENT)
$(TARGET_CLIENT): $(OBJS_CLIENT) shared
	$(CXX) $(OBJS_CLIENT) -o $(TARGET_CLIENT) $(OBJS_SHARED) $(LIBS)

shared: $(OBJS_SHARED)

$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(OBJS) $(SRCS)

android: $(TARGET_ANDROID_APK) $(TARGET_ANDROID_DATA)
android_apk: $(TARGET_ANDROID_APK)
android_data: $(TARGET_ANDROID_DATA)
$(TARGET_ANDROID_APK):
	rm -rf android/jni/src
	ln -s $(realpath $(SRC_DIR)) android/jni
	cd android/jni;ndk-build
	cd android;ant debug
	mv android/bin/SDLActivity-debug.apk $(TARGET_ANDROID_APK)
$(TARGET_ANDROID_DATA):
	mkdir tee3d
	mv data/shaders data/shaders-gl
	mv data/shaders-gles data/shaders
	mv data tee3d/data
	zip -r $(TARGET_ANDROID_DATA) tee3d
	mv tee3d/data data
	mv data/shaders data/shaders-gles
	mv data/shaders-gl data/shaders
	rm -r tee3d

clean:
	rm -rf $(TARGET) $(OBJS)
	rm -rf android/jni/src
	rm -rf android/obj/*
	rm -rf android/gen/*
	rm -rf android/bin/*
