#include "Input.h"

class Input *pInput;
Input *g_Input() { return pInput != nullptr ? pInput : new Input(); }

Input::Input() : ClientComponent() {
	pInput = this;
	mouse.resize(SDL_BUTTON_RIGHT + 1);
	quit = false;
	mouseX = 0;
	mouseY = 0;
	mouseWheel = 0;
}
Input::~Input() { pInput = nullptr; }
void Input::Tick() {
	quit = false;
	mouseX = 0;
	mouseY = 0;
	mouseWheel = 0;
	SDL_Event sdlevent;
	while (SDL_PollEvent(&sdlevent) != 0) {
		switch (sdlevent.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			keyboard[sdlevent.key.keysym.sym] = 1;
			break;
		case SDL_KEYUP:
			keyboard[sdlevent.key.keysym.sym] = 0;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouse[sdlevent.button.button] = 1;
			break;
		case SDL_MOUSEBUTTONUP:
			mouse[sdlevent.button.button] = 0;
			break;
		case SDL_MOUSEMOTION:
			mouseX = sdlevent.motion.xrel;
			mouseY = sdlevent.motion.yrel;
			if (mouseX > 100000) {
				mouseX = 0;
			}
			if (mouseY > 100000) {
				mouseY = 0;
			}
			break;
		case SDL_MOUSEWHEEL:
			mouseWheel = sdlevent.wheel.y;
			break;
		}
	}
}
