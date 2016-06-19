#include "UI.h"
#include <client/components/ui/View.h>

class UI *pUI;
UI *g_UI() { return pUI ? pUI : new UI(); }

UI::UI() : ClientComponent() {
	pUI = this;
}
UI::~UI() { pUI= 0; }
void UI::Tick() {
	for(View *v : registredViews)
		if(v->visible)
			v->Validate();
}
void UI::RegisterView(View *view) { registredViews.insert(view); }
void UI::UnregisterView(View *view) { registredViews.erase(view); }
