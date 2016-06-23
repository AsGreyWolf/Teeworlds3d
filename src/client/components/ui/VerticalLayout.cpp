#include "VerticalLayout.h"

void VerticalLayout::Validate() {
	Layout::Validate();
	int count = children.size();
	float dy = workspace.h / count;
	for(int i=0; i < count; i++)
		children[i]->container = quad2(workspace.x, workspace.y + dy * i, workspace.w, dy);
}
