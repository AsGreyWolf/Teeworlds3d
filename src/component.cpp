#include "component.h"

using namespace tee3d;
using namespace std;

list<component::manager::value_type> component::manager::data;

template <class T, class... Args>
weak_ptr<T> component::manager::emplace(Args... args) {
	data.push_back(make_shared<T>(args...));
	return data.back();
}
void component::manager::cleanup() {
	while (!data.empty()) {
		data.pop_back();
	}
}
void component::manager::tick() {
	for (value_type &component : data) {
		component->tick();
	}
}

template <class T>
typename component::wrapper<T>::pointer component::wrapper<T>::operator->() {
	if (!ptr) {
		ptr = manager::emplace<component_type>();
	}
	return ptr.get();
}
template <class T>
typename component::wrapper<T>::const_pointer component::wrapper<T>::
operator->() const {
	return ptr.get();
}
template <class T> component::wrapper<T>::operator bool() const { return ptr; }
