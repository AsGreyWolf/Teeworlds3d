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
	shared/SharedComponent.cpp \
	shared/Console.cpp \
	shared/System.cpp \
	shared/World.cpp \
	shared/world/Player.cpp \
	client/ClientComponent.cpp \
	client/components/Camera.cpp \
	client/components/Client.cpp \
	client/components/Graphics.cpp \
	client/components/ImageLoader.cpp \
	client/components/Input.cpp \
	client/components/Loading.cpp \
	client/components/Map.cpp \
	client/components/Resources.cpp \
	client/components/TextGenerator.cpp \
	client/components/UI.cpp \
	client/components/graphics/Model.cpp \
	client/components/graphics/Shader.cpp \
	client/components/graphics/Texture.cpp \
	client/components/graphics/geometry/Geometry2d.cpp \
	client/components/graphics/geometry/Geometry3d.cpp \
	client/components/graphics/geometry/ObjModel.cpp \
	client/components/graphics/geometry/Primitives.cpp \
	client/components/graphics/geometry/Sphere.cpp \
	client/components/graphics/models/Model2d.cpp \
	client/components/graphics/models/Model3d.cpp \
	client/components/graphics/models/Particles.cpp \
	client/components/graphics/models/PlayerModel.cpp \
	client/components/graphics/models/ShadowModel.cpp \
	client/components/graphics/shaders/Shader2d.cpp \
	client/components/graphics/shaders/Shader3d.cpp \
	client/components/graphics/shaders/Shader3dComposer.cpp \
	client/components/graphics/shaders/ShaderParticle.cpp \
	client/components/graphics/shaders/ShaderShadow.cpp \
	client/components/graphics/shaders/ShaderTexture.cpp \
	client/components/ui/HorizontalLayout.cpp \
	client/components/ui/Image.cpp \
	client/components/ui/Label.cpp \
	client/components/ui/Layout.cpp \
	client/components/ui/VerticalLayout.cpp \
	client/components/ui/View.cpp \
	client/components/ui/Widget.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf SDL2_image

LOCAL_LDLIBS := -lGLESv3 -llog

include $(BUILD_SHARED_LIBRARY)
