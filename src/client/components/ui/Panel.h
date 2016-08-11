#ifndef IMAGE_H
#define IMAGE_H

#include "View.h"
#include <client/components/graphics/Texture.h>
#include <client/components/graphics/models/Model2d.h>

enum PANEL_FLAGS {
	FLIP_X = 0x01,
	FLIP_Y = 0x02,
};

class Panel : public View {
public:
	Panel(const Texture &texture, int flags = 0);
	Panel(int flags = 0);
	Panel(const Panel &second);
	virtual ~Panel();

	virtual void Validate() override;

	Texture texture;
	glm::vec4 color;

protected:
	int flags;
	Model2d model;
};

#endif
