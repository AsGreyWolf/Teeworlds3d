#include "UI.h"
#include <client/components/Graphics.h>
#include <client/components/Input.h>
#include <client/components/Resources.h>
#include <client/components/ui/Layout.h>
#include <client/components/ui/Panel.h>

class UI *pUI;
UI *g_UI() { return pUI ? pUI : new UI(); }

UI::UI() : ClientComponent() {
	pUI = this;
	screenLayout = new Layout();
	screenLayout->container = g_Graphics()->screen;
	cursor = new Panel(g_Resources()->textureCursor);
	cursor->size = glm::vec2(0.1f, 0.1f);
	screenLayout->Add(cursor);
	SDL_ShowCursor(0);
	DisableCursor();
}
UI::~UI() { pUI = 0; }
void UI::Tick() {
	if (CursorEnabled()) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		cursorPosition.x = g_Graphics()->to_screen(x) + g_Graphics()->screen.x;
		cursorPosition.y = -g_Graphics()->to_screen(y) + g_Graphics()->screen.y +
		                   g_Graphics()->screen.h;
		cursor->Show();
		cursor->padding[BORDER_LEFT] = cursorPosition.x - g_Graphics()->screen.x;
		cursor->padding[BORDER_BOTTOM] =
		    cursorPosition.y - g_Graphics()->screen.y - cursor->size.y;
	} else {
		cursor->Hide();
	}
	for (View *v : registredViews)
		v->Validate();
	if (CursorEnabled()) {
		bool buttonState = g_Input()->mouse[SDL_BUTTON_LEFT];
		static bool lastButtonState = false;
		View *target = screenLayout->Select(cursorPosition);
		static View *clickedTarget = NULL;
		static glm::vec2 lastCursorPosition;
		if (target && buttonState && !lastButtonState) {
			target->OnMouseDown(cursorPosition);
			clickedTarget = target;
			lastCursorPosition = cursorPosition;
		} else if (target && lastButtonState && !buttonState) {
			target->OnMouseUp(cursorPosition);
			if (clickedTarget == target)
				target->OnClick(cursorPosition);
			else
				target->OnDrop(cursorPosition);
			clickedTarget = NULL;
		}
		if (clickedTarget && buttonState && cursorPosition != lastCursorPosition) {
			clickedTarget->OnDrag(cursorPosition);
		}
		lastButtonState = buttonState;
		lastCursorPosition = cursorPosition;
	}
}
void UI::RegisterView(View *view) { registredViews.insert(view); }
void UI::UnregisterView(View *view) { registredViews.erase(view); }
void UI::EnableCursor() { SDL_SetRelativeMouseMode(SDL_FALSE); }
void UI::DisableCursor() { SDL_SetRelativeMouseMode(SDL_TRUE); }
bool UI::CursorEnabled() const { return !SDL_GetRelativeMouseMode(); }
