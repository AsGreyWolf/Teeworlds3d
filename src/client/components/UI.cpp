#include "UI.h"
#include <client/components/Graphics.h>

class UI *pUI;
UI *g_UI() { return pUI ? pUI : new UI(); }

UI::UI() : ClientComponent() {
	pUI = this;
	screenLayout = new Layout();
	screenLayout->container = g_Graphics()->screen;
}
UI::~UI() { pUI= 0; }
void UI::Tick() {
	for(View *v : registredViews)
		if(v->isVisible())
			v->Validate();
}
void UI::RegisterView(View *view) { registredViews.insert(view); }
void UI::UnregisterView(View *view) { registredViews.erase(view); }
