#include "Console.h"

#include <iostream>

class Console *pConsole;
Console *g_Console() { return pConsole ? pConsole : new Console(); }

Console::Console() : SharedComponent() { pConsole = this; };
Console::~Console() { pConsole = 0; };
void Console::Err(const std::string &c) {
	std::cerr << "[ERROR] " << c << std::endl;
};
void Console::Info(const std::string &c) {
	std::cout << "[INFO] " << c << std::endl;
};
