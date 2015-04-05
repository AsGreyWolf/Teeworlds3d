#include "Console.h"
#include <iostream>

class Console* mp_Console;
Console* m_Console(){	return mp_Console;	}

Console::Console(){
	mp_Console = this;
};
Console::~Console(){
	mp_Console = 0;
};
void Console::Tick(){}
void Console::Err(string c){
	std::cerr << "[ERROR] " << c << std::endl;
};
void Console::Info(string c){
	std::cout << "[INFO] " << c << std::endl;
};