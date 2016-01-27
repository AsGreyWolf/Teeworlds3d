#include "Console.h"
#include <iostream>

class Console* pConsole;
Console* g_Console(){	return pConsole;	}

Console::Console() :SharedComponent() {
	pConsole = this;
};
Console::~Console(){
	pConsole = 0;
};
void Console::Tick(){
	SharedComponent::Tick();
}
void Console::Err(const string& c){
	std::cerr << "[ERROR] " << c << std::endl;
};
void Console::Info(const string& c){
	std::cout << "[INFO] " << c << std::endl;
};