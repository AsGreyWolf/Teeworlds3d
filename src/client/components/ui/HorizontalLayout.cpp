#include "HorizontalLayout.h"

void HorizontalLayout::Validate() {
	if (!isVisible()) {
		return;
	}
	Layout::Validate();
	int count = children.size();
	float dx = workspace.w / count;
	for (int i = 0; i < count; i++) {
		children[i]->container =
		    quad2(workspace.x + dx * i, workspace.y, dx, workspace.h);
	}
}
View *HorizontalLayout::Select(const glm::vec2 &position) {
	int count = children.size();
	float dx = workspace.w / count;
	int i = glm::min(static_cast<int>((position.x - workspace.x) / dx), count - 1);
	return children[i]->Select(position);
}
