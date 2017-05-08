#pragma once
#include "managed_base.hpp"
#include "manager.hpp"

namespace tee3d::shared::mgr {
template <typename Element> struct managed : managed_base {
	managed() { get_manager<Element>().push((Element *)this); }
	~managed() override { get_manager<Element>().pop((Element *)this); }
	void tick() override{};
};
}
