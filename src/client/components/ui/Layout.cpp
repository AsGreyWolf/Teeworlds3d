#include "Layout.h"
#include <algorithm>

Layout::Layout() : View() {}
Layout::Layout(const Layout &second) : Layout() { *this = second; }
Layout::~Layout() {}
void Layout::Show() {
	View::Show();
	for (View *v : children) {
		v->Show();
	}
}
void Layout::Hide() {
	for (View *v : children) {
		v->Hide();
	}
}
void Layout::Validate() {
	if (!isVisible())
		return;
	View::Validate();
	workspace =
	    quad2(element.x + margin[BORDER_LEFT], element.y + margin[BORDER_BOTTOM],
	          element.w - margin[BORDER_RIGHT] - margin[BORDER_LEFT],
	          element.h - margin[BORDER_TOP] - margin[BORDER_BOTTOM]);
	int count = children.size();
	float layerSize = (maxLayer - minLayer) / count;
	for (int i = 0; i < count; i++) {
		View &v = *children[i];
		v.minLayer = minLayer + layerSize * i;
		v.maxLayer = v.minLayer + layerSize;
		v.container = workspace;
	}
}
View *Layout::Select(const glm::vec2 &position) {
	int count = children.size();
	View *v = NULL;
	for (int i = 0; i < count && !(v = children[i]->Select(position)); i++)
		;
	return v;
}
void Layout::Add(View *view) { children.push_back(view); }
void Layout::Remove(View *view) {
	std::remove(children.begin(), children.end(), view);
}
