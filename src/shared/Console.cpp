#include "Console.h"
#include <iostream>

class Console* pConsole;
Console* g_Console(){	return pConsole;	}

Console::Console(){
	pConsole = this;
};
Console::~Console(){
	pConsole = 0;
};
void Console::Tick(){}
void Console::Err(string c){
	std::cerr << "[ERROR] " << c << std::endl;
};
void Console::Info(string c){
	std::cout << "[INFO] " << c << std::endl;
};