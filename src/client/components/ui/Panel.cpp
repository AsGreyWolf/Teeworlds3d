#include "Panel.h"
#include <client/components/graphics/geometry/Primitives.h>
#include <client/components/Resources.h>

Panel::Panel(const Texture &t, int f) : View(), texture(t), flags(f) {
	color = glm::vec4(1, 1, 1, 0);
}
Panel::Panel(int f) : Panel(g_Resources()->textureBlank, f) { }
Panel::Panel(const Panel &second) : View() {
	*this = second;
}
Panel::~Panel() { }
void Panel::Validate() {
	if (!isVisible()) {
		model.Disable();
		return;
	}
	View::Validate();
	model.depth = minLayer;
	model.texture = texture;
	model.color = color;
	model.Clear();
	model.Add(Quad(element,quad2(flags&FLIP_X?1:0,flags&FLIP_Y?1:0,flags&FLIP_X?-1:1,flags&FLIP_Y?-1:1)));
	model.Enable();
}
