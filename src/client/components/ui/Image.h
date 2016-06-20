#ifndef IMAGE_H
#define IMAGE_H

#include "View.h"
#include <client/components/graphics/Texture.h>
#include <client/components/graphics/models/Model2d.h>

class Image : public View {
public:
	Image();
	Image(const Image &second);
	virtual ~Image();

	virtual void Validate() override;

	Texture texture;

private:
	Model2d model;
};

#endif
