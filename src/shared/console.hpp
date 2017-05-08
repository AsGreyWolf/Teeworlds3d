#include <iostream>
#include <shared/tools/managed.hpp>
#include <string>

namespace tee3d::shared {
struct console : mgr::managed<console> {
	void error(const std::string &msg);
};
}
