#ifndef VERTICALLAYOUT_H
#define VERTICALLAYOUT_H

#include "Layout.h"

class VerticalLayout : public Layout {
public:
	void Validate() override;
	View *Select(const glm::vec2 &position) override;
};

#endif
