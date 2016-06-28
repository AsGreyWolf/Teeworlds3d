#include "HorizontalLayout.h"

void HorizontalLayout::Validate() {
	if (!isVisible()) return;
	Layout::Validate();
	int count = children.size();
	float dx = workspace.w / count;
	for(int i=0; i < count; i++)
		children[i]->container = quad2(workspace.x + dx * i, workspace.y, dx, workspace.h);
}
void HorizontalLayout::OnClick(const glm::vec2 &position) {
	int count = children.size();
	float dx = workspace.w / count;
	int i = glm::min((int)((position.x - workspace.x) / dx), count - 1);
	children[i]->Click(position);
}
