#ifndef IMAGE_H
#define IMAGE_H

#include "View.h"
#include <client/components/graphics/Texture.h>
#include <client/components/graphics/models/Model2d.h>

class Image : public View {
public:
	Image(const Texture &texture);
	Image(const Image &second);
	virtual ~Image();

	virtual void Validate() override;

	void SetTexture(const Texture &texture);

private:
	Model2d model;
};

#endif
