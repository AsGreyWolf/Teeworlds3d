#include "Graphics.h"

#include <shared/Console.h>
#include <client/components/graphics/Shader.h>

class Graphics *pGraphics;
Graphics *g_Graphics() { return pGraphics ? pGraphics : new Graphics(); }

Graphics::Graphics() : ClientComponent() {
	pGraphics = this;

	int w = 1024; // TODO: config
	int h = 768;
	if (h == 0) {
		h = 1;
	}
	screenSize = glm::vec2(w, h);
	screenAspect = (float)w / h;
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
	if ((window = SDL_CreateWindow("", 50, 50, w, h,
	                               SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)) ==
	    NULL) {
		g_Console()->Err("Could not create window: " + std::string(SDL_GetError()));
		return; // need exceptions
	}
	if ((renderer = SDL_CreateRenderer(window, -1, 0)) == NULL) {
		g_Console()->Err("Could not get renderer: " + std::string(SDL_GetError()));
		return; // TODO: need exceptions
	}
	if ((context = SDL_GL_CreateContext(window)) == NULL) {
		g_Console()->Err("Could not get context: " + std::string(SDL_GetError()));
		return; // TODO: exceptions
	}
	SDL_GL_SetSwapInterval(0);
	glewInit();
	g_Console()->Info("Initialized OpenGL " +
	                  std::string((char *)glGetString(GL_VERSION)));

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0, 0.75f, 1, 1);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPolygonMode(GL_FRONT, GL_FILL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_FOG_HINT, GL_NICEST);
	glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glLineWidth(3);
	glPointSize(3);

	SDL_SetRelativeMouseMode(SDL_TRUE);
}
Graphics::~Graphics() {
	Shader::ClearShaders();
	SDL_GL_DeleteContext(context);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	pGraphics = NULL;
}
glm::mat4 orthoMatrix =
    glm::ortho(-320.0f, 320.0f, -320.0f, 320.0f, 0.0f, 1.0f);
void Graphics::Tick() {
	Shader::RenderShaders();
	SDL_GL_SwapWindow(window);
}
int Graphics::to_pixels(float coord) { return coord * screenSize.y / 2; }
float Graphics::to_screen(int pix) { return pix * 2.0f / screenSize.y; }
SDL_Surface *Graphics::to_RGBA(SDL_Surface *src) {
	if (src == NULL)
		return NULL;
	return SDL_ConvertSurfaceFormat(src, SDL_PIXELFORMAT_ABGR8888, 0);
}
