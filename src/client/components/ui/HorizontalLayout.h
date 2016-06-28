#ifndef HORIZONTALLAYOUT_H
#define HORIZONTALLAYOUT_H

#include "Layout.h"

class HorizontalLayout : public Layout {
public:
	void Validate() override;
	void OnClick(const glm::vec2 &position) override;
};

#endif
