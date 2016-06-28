#ifndef VERTICALLAYOUT_H
#define VERTICALLAYOUT_H

#include "Layout.h"

class VerticalLayout : public Layout {
public:
	void Validate() override;
	void OnClick(const glm::vec2 &position) override;
};

#endif
