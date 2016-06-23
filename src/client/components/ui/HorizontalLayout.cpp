#include "HorizontalLayout.h"

void HorizontalLayout::Validate() {
	Layout::Validate();
	int count = children.size();
	float dx = workspace.w / count;
	for(int i=0; i < count; i++)
		children[i]->container = quad2(workspace.x + dx * i, workspace.y, dx, workspace.h);
}
