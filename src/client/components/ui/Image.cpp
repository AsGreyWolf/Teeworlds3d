#include "Image.h"
#include <client/components/graphics/geometry/Primitives.h>

Image::Image() : View() { }
Image::Image(const Image &second) : Image() {
	*this = second;
}
Image::~Image() { }
void Image::Validate() {
	View::Validate();
	model = Model2d();
	model.texture = texture;
	model.Add(Quad(workspace));
	if(isVisible())
		model.Enable();
}
