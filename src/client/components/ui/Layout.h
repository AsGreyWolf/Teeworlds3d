#ifndef LAYOUT_H
#define LAYOUT_H

#include "View.h"
#include <vector>

class Layout : public View {
public:
	Layout();
	Layout(const Layout &second);
	virtual ~Layout();

	void Show() override;
	void Hide() override;
	virtual void Validate() override;
	virtual View *Select(const glm::vec2 &position) override;
	void Add(View *view);
	void Remove(View *view);

	float margin[NUM_BORDERS] = {0, 0, 0, 0};

protected:
	quad2 workspace;
	std::vector<View *> children;
};

#endif
