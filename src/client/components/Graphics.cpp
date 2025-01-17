#include "Graphics.h"

#include <client/components/graphics/Shader.h>
#include <shared/Console.h>

class Graphics *pGraphics;
Graphics *g_Graphics() {
	return pGraphics != nullptr ? pGraphics : new Graphics();
}

Graphics::Graphics() : ClientComponent() {
	pGraphics = this;

	int w = 1024; // TODO: config
	int h = 768;
	if (h == 0) {
		h = 1;
	}
	screenSize = glm::vec2(w, h);
	screenAspect = w * 1.0f / h;
	screen = quad2(-1 * screenAspect, -1, 2 * screenAspect, 2);

	SDL_version ver;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		g_Console()->Err("Unable to initialize SDL Video: " +
		                 std::string(SDL_GetError()));
		return; // TODO: need exceptions
	}
	SDL_GetVersion(&ver);
	g_Console()->Info("Initialized SDL Video " + std::to_string(ver.major) + "." +
	                  std::to_string(ver.minor) + "." + std::to_string(ver.patch));
	// SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	// SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if ((window = SDL_CreateWindow(
	         "", 50, 50, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)) == nullptr) {
		g_Console()->Err("Could not create window: " + std::string(SDL_GetError()));
		return; // need exceptions
	}
	if ((renderer = SDL_CreateRenderer(window, -1, 0)) == nullptr) {
		g_Console()->Err("Could not get renderer: " + std::string(SDL_GetError()));
		return; // TODO: need exceptions
	}
	if ((context = SDL_GL_CreateContext(window)) == nullptr) {
		g_Console()->Err("Could not get context: " + std::string(SDL_GetError()));
		return; // TODO: exceptions
	}
	SDL_GL_SetSwapInterval(0);
#ifndef __ANDROID__
	glewInit();
#endif
	g_Console()->Info("Initialized OpenGL " +
	                  std::string((char *)glGetString(GL_VERSION)));

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#ifndef __ANDROID__
	glEnable(GL_MULTISAMPLE);
#endif
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0, 0.75f, 1, 1);

	glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);

	glLineWidth(3);
#ifndef __ANDROID__
	glPointSize(3);
#endif
}
Graphics::~Graphics() {
	Shader::ClearShaders();
	SDL_GL_DeleteContext(context);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	pGraphics = nullptr;
}
void Graphics::Tick() {
	Shader::RenderShaders();
	SDL_GL_SwapWindow(window);
}
int Graphics::to_pixels(float coord) { return coord * screenSize.y / 2; }
float Graphics::to_screen(int pix) { return pix * 2.0f / screenSize.y; }
SDL_Surface *Graphics::to_RGBA(SDL_Surface *src) {
	if (src == nullptr) {
		return nullptr;
	}
	return SDL_ConvertSurfaceFormat(src, SDL_PIXELFORMAT_ABGR8888, 0);
}
