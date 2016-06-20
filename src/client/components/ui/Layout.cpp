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
void Layout::Remove(View *view) {
	remove(children.begin(), children.end(), view);
}
