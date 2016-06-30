#include "Image.h"
#include <client/components/graphics/geometry/Primitives.h>

Image::Image(const Texture &texture, int f) : View(), flags(f) {
	SetTexture(texture);
}
Image::Image(const Image &second) : View() {
	*this = second;
}
Image::~Image() { }
void Image::Validate() {
	if (!isVisible()) {
		model.Disable();
		return;
	}
	View::Validate();
	model.depth = minLayer;
	model.Clear();
	model.Add(Quad(element,quad2(flags&FLIP_X?1:0,flags&FLIP_Y?1:0,flags&FLIP_X?-1:1,flags&FLIP_Y?-1:1)));
	model.Enable();
}
void Image::SetTexture(const Texture &t) {
	model.texture = t;
}
