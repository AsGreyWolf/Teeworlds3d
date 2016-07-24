#include "Input.h"

class Input *pInput;
Input *g_Input() { return pInput ? pInput : new Input(); }

Input::Input() : ClientComponent() {
	pInput = this;
	mouse.resize(SDL_BUTTON_RIGHT + 1);
	quit = 0;
	mouseX = 0;
	mouseY = 0;
	mouseWheel = 0;
}
Input::~Input() { pInput = 0; }
void Input::Tick() {
	quit = 0;
	mouseX = 0;
	mouseY = 0;
	mouseWheel = 0;
	SDL_Event sdlevent;
	while (SDL_PollEvent(&sdlevent)) {
		switch (sdlevent.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			keyboard[sdlevent.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			keyboard[sdlevent.key.keysym.sym] = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouse[sdlevent.button.button] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			mouse[sdlevent.button.button] = false;
			break;
		case SDL_MOUSEMOTION:
			mouseX = sdlevent.motion.xrel;
			mouseY = sdlevent.motion.yrel;
			if (mouseX > 100000)
				mouseX = 0;
			if (mouseY > 100000)
				mouseY = 0;
			break;
		case SDL_MOUSEWHEEL:
			mouseWheel = sdlevent.wheel.y;
			break;
		}
	}
}
