#include "Panel.h"
#include <client/components/Resources.h>
#include <client/components/graphics/geometry/Primitives.h>

Panel::Panel(Texture t, int f) : View(), texture(std::move(t)), flags(f) {
	color = glm::vec4(1, 1, 1, 0);
}
Panel::Panel(int f) : Panel(g_Resources()->textureBlank, f) {}
Panel::Panel(const Panel &second) : View() { *this = second; }
Panel::~Panel() = default;
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
	model.Add(Quad(element, quad2((flags & FLIP_X) != 0 ? 1 : 0,
	                              (flags & FLIP_Y) != 0 ? 1 : 0,
	                              (flags & FLIP_X) != 0 ? -1 : 1,
	                              (flags & FLIP_Y) != 0 ? -1 : 1)));
	model.Enable();
}
