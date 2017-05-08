#pragma once
#include <memory>

namespace tee3d::shared::mgr {
struct component {
	size_t id = -1;
	component() = default;
	component(const component &) = delete;
	component(component &&) = default;
	component &operator=(const component &) = delete;
	component &operator=(component &&) = default;
	virtual ~component() = default;

	virtual void tick() = 0;
};
}
