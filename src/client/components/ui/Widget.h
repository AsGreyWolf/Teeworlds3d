#ifndef WIDGET_H
#define WIDGET_H

#include "View.h"

template <typename T>
class Widget : public View {
public:
	using value_type = T;
	Widget(value_type *value);
	// TODO: cursor events: click, drag, etc

protected:
	value_type *value;
};

#endif
