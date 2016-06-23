#ifndef VIEW_H
#define VIEW_H

#include <tools/vmath.h>

enum BORDER {
	BORDER_TOP = 0,
	BORDER_RIGHT,
	BORDER_BOTTOM,
	BORDER_LEFT,
	NUM_BORDERS
};
enum ALIGN {
	ALIGN_LEFT = 0,
	ALIGN_CENTER,
	ALIGN_RIGHT,

	ALIGN_BOTTOM = 0,
	// ALIGN_CENTER,
	ALIGN_TOP = 2
};
#define SIZE_FILL (-1.0f)

class View {
public:
	View();
	View(const View &second);
	virtual ~View();

	inline bool isVisible() const { return visible; }
	virtual void Show();
	virtual void Hide();
	virtual void Validate();

	float padding[NUM_BORDERS] = {0, 0, 0, 0};
	glm::uvec2 align;
	glm::vec2 size = glm::vec2(SIZE_FILL, SIZE_FILL);
	quad2 container;
	float minLayer = 0.0f;
	float maxLayer = 1.0f;

protected:
	quad2 element;

private:
	bool visible = true;
};

#endif
