#include "UI.h"
#include <client/components/Graphics.h>
#include <client/components/Resources.h>
#include <client/components/ui/Image.h>
#include <client/components/ui/Layout.h>

class UI *pUI;
UI *g_UI() { return pUI ? pUI : new UI(); }

UI::UI() : ClientComponent() {
	pUI = this;
	screenLayout = new Layout();
	screenLayout->container = g_Graphics()->screen;
	cursor = new Image(g_Resources()->textureCursor);
	cursor->size = glm::vec2(0.1f, 0.1f);
	screenLayout->Add(cursor);
	SDL_ShowCursor(0);
	DisableCursor();
}
UI::~UI() { pUI= 0; }
void UI::Tick() {
	cursorEnabled = !SDL_GetRelativeMouseMode();
	if(CursorEnabled()) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		cursorPosition.x = g_Graphics()->to_screen(x) + g_Graphics()->screen.x;
		cursorPosition.y = - g_Graphics()->to_screen(y) + g_Graphics()->screen.y + g_Graphics()->screen.h - cursor->size.y;
		cursor->Show();
		cursor->padding[BORDER_LEFT] = cursorPosition.x - g_Graphics()->screen.x;
		cursor->padding[BORDER_BOTTOM] = cursorPosition.y - g_Graphics()->screen.y;
	} else {
		cursor->Hide();
	}
	for(View *v : registredViews)
		if(v->isVisible())
			v->Validate();
}
void UI::RegisterView(View *view) { registredViews.insert(view); }
void UI::UnregisterView(View *view) { registredViews.erase(view); }
void UI::EnableCursor() {
	SDL_SetRelativeMouseMode(SDL_FALSE);
}
void UI::DisableCursor() {
	SDL_SetRelativeMouseMode(SDL_TRUE);
}
