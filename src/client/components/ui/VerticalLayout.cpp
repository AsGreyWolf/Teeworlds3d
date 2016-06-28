#include "VerticalLayout.h"

void VerticalLayout::Validate() {
	if (!isVisible()) return;
	Layout::Validate();
	int count = children.size();
	float dy = workspace.h / count;
	for(int i=0; i < count; i++)
		children[i]->container = quad2(workspace.x, workspace.y + dy * i, workspace.w, dy);
}
void VerticalLayout::OnClick(const glm::vec2 &position) {
	int count = children.size();
	float dy = workspace.h / count;
	int i = glm::min((int)((position.y - workspace.y) / dy), count - 1);
	children[i]->Click(position);
}
