#include "Widget.h"

template <typename T>
Widget<T>::Widget(value_type *v) : View() {
	value = v;
}
