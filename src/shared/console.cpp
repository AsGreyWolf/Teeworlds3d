#include "console.hpp"

namespace tee3d::shared {
void console::error(const std::string &msg) {
	std::cerr << "[ERROR]" << msg << std::endl;
}
}
