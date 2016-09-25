#ifndef WIDGET_H
#define WIDGET_H

#include "View.h"

template <typename T> class Widget : public View {
public:
	using value_type = T;
	explicit Widget(value_type &value);

protected:
	value_type &value;
};

#endif
