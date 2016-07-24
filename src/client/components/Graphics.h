#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../ClientComponent.h"
#define GLEW_STATIC
#ifdef __ANDROID__
	#include <GLES3/gl3.h>
#else
	#include <glew.h>
#endif
#include <tools/vmath.h>

class Resources;

class Graphics : public ClientComponent {
private:
	Graphics();
	friend Graphics *g_Graphics();

public:
	~Graphics() override;
	void Tick() override;

	SDL_Surface *to_RGBA(SDL_Surface *src);
	int to_pixels(float coord);
	float to_screen(int pix);

	quad2 screen;
	float screenAspect;
	glm::vec2 screenSize;

private:
	SDL_GLContext context;
	SDL_Renderer *renderer;
	SDL_Window *window;
};
Graphics *g_Graphics();

#endif
