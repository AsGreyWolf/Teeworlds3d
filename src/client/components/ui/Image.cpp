#include "Image.h"
#include <client/components/graphics/geometry/Primitives.h>

Image::Image(const Texture &texture) : View() {
	SetTexture(texture);
}
Image::Image(const Image &second) : View() {
	*this = second;
}
Image::~Image() { }
void Image::Validate() {
	View::Validate();
	model.Clear();
	model.Add(Quad(element));
	if(isVisible())
		model.Enable();
}
void Image::SetTexture(const Texture &t) {
	model.texture = t;
}
