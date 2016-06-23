#include "View.h"
#include <client/components/UI.h>

View::View() {
	g_UI()->RegisterView(this);
}
View::View(const View &second) : View() {
	*this = second;
}
View::~View() {
	g_UI()->UnregisterView(this);
}
void View::Show() {
	visible = true;
}
void View::Hide() {
	visible = false;
}
void View::Validate() {
	element = quad2(container.x + padding[BORDER_LEFT],
	                container.y + padding[BORDER_BOTTOM],
	                container.w - padding[BORDER_RIGHT] - padding[BORDER_LEFT],
	                container.h - padding[BORDER_TOP] - padding[BORDER_BOTTOM]);

	// apply alignment
	float x = element.x;
	float y = element.y;
	float w = element.w;
	float h = element.h;
	if (size.x >= 0)
		w = size.x;
	switch (align.x) {
		case ALIGN_CENTER:
			x = element.x + element.w / 2 - w / 2;
			break;
		case ALIGN_RIGHT:
			x = element.x + element.w - w;
			break;
	}
	if (size.y >= 0)
		h = size.y;
	switch (align.y) {
		case ALIGN_CENTER:
			y = element.y + element.h / 2 - h / 2;
			break;
		case ALIGN_TOP:
			y = element.y + element.h - h;
			break;
	}
	element = quad2(x, y, w, h);
}
