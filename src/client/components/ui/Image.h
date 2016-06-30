#ifndef IMAGE_H
#define IMAGE_H

#include "View.h"
#include <client/components/graphics/Texture.h>
#include <client/components/graphics/models/Model2d.h>

enum IMAGE_MODE {
	FLIP_X = 0x01,
	FLIP_Y = 0x02,
};

class Image : public View {
public:
	Image(const Texture &texture, int flags = 0);
	Image(const Image &second);
	virtual ~Image();

	virtual void Validate() override;

	void SetTexture(const Texture &texture);

protected:
	int flags;
	Model2d model;
};

#endif
