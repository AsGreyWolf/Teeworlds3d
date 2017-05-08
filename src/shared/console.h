#ifndef CONSOLE_H
#define CONSOLE_H

#include "../component.h"

#include <string>

namespace tee3d {
namespace shared {
using std::string;
class console_component : public component {
private:
	console_component();

public:
	~console_component() override;

	template <class T> void err(T &&c);
	template <class T> void info(T &&c);
};
using console = component::wrapper<console_component>;
};
};

#endif
