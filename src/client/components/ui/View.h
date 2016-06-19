#ifndef VIEW_H
#define VIEW_H

#include <tools/vmath.h>

class View {
public:
	View();
	View(const View &second);
	virtual ~View();

	virtual void Validate();

	enum DIRECTIONS {
		TOP = 0,
		RIGHT,
		BOTTOM,
		LEFT,
		NUM_DIRECTIONS
	};
	float margin[NUM_DIRECTIONS];
	float padding[NUM_DIRECTIONS];
	#define FILL_PARENT glm::vec2(-1, -1);
	glm::vec2 size;
	quad2 container;
	bool visible = true;

protected:
	quad2 element;
	quad2 workspace;
};

#endif
