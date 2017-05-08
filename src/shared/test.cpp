#include <shared/console.hpp>
#include <shared/tools/manager.hpp>
using namespace tee3d::shared;
using namespace tee3d::shared::mgr;
int main() {
	std::cout << get_manager<managed_base>().registry.size() << std::endl;
	{
		console csl;
		std::cout << get_manager<managed_base>().registry[0] << std::endl;
		csl.error("test");
	}
	std::cout << get_manager<managed_base>().registry[0] << std::endl;
}
