#pragma once
#include <memory>

namespace tee3d::shared::mgr {
struct managed_base {
	size_t id = -1;
	managed_base() = default;
	managed_base(const managed_base &) = delete;
	managed_base(managed_base &&) = default;
	managed_base &operator=(const managed_base &) = delete;
	managed_base &operator=(managed_base &&) = default;
	virtual ~managed_base() = default;

	virtual void tick() = 0;
};
}
