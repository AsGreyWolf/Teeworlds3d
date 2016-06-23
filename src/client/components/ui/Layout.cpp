#include "Layout.h"

Layout::Layout() : View() { }
Layout::Layout(const Layout &second) : Layout() {
	*this = second;
}
Layout::~Layout() { }
void Layout::Show() {
	View::Show();
	for(View *v : children) {
		v->Show();
	}
}
void Layout::Hide() {
	for(View *v : children) {
		v->Hide();
	}
}
void Layout::Validate() {
	View::Validate();
	workspace = quad2(element.x + margin[BORDER_LEFT],
	                  element.y + margin[BORDER_BOTTOM],
	                  element.w - margin[BORDER_RIGHT] - margin[BORDER_LEFT],
	                  element.h - margin[BORDER_TOP] - margin[BORDER_BOTTOM]);
	int count = children.size();
	float layerSize = (maxLayer - minLayer) / count;
	for(int i=0; i < count; i++) {
		View &v = *children[i];
		v.minLayer = minLayer + layerSize * i;
		v.maxLayer = v.minLayer + layerSize;
		v.container = workspace;
	}
}
void Layout::Add(View *view) {
	children.push_back(view);
}
