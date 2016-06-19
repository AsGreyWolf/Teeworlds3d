#include "View.h"
#include <client/components/UI.h>

View::View() {
	g_UI()->RegisterView(this);
}
View::View(const View &second) {
	*this = second;
	g_UI()->RegisterView(this);
}
View::~View() {
	g_UI()->UnregisterView(this);
}
void View::Validate() {
	float x = container.p00.x + padding[LEFT];
	float y = container.p00.y + padding[BOTTOM];
	float w = container.p11.x - x - padding[RIGHT];
	float h = container.p11.y - y - padding[TOP];
	element = quad2(x, y, w, h);
	x += margin[LEFT];
	y += margin[BOTTOM];
	w -= margin[RIGHT];
	h -= margin[TOP];
	if(size.x < 0 || size.y < 0)
		workspace = quad2(x, y, w, h);
	else
		workspace = quad2(x, y, size.x, size.y);
}
