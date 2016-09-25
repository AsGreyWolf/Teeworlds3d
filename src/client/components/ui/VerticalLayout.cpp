#include "VerticalLayout.h"

void VerticalLayout::Validate() {
	if (!isVisible()) {
		return;
	}
	Layout::Validate();
	int count = children.size();
	float dy = workspace.h / count;
	for (int i = 0; i < count; i++) {
		children[i]->container =
		    quad2(workspace.x, workspace.y + dy * i, workspace.w, dy);
	}
}
View *VerticalLayout::Select(const glm::vec2 &position) {
	int count = children.size();
	float dy = workspace.h / count;
	int i = glm::min(static_cast<int>((position.y - workspace.y) / dy), count - 1);
	return children[i]->Select(position);
}
