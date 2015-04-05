#ifndef CONSOLE_H
#define CONSOLE_H

#include "SharedComponent.h"
#include <string>

class Console : public SharedComponent{
public:
	Console();
	~Console();

	///<summary>Tick the component</summary>
	void Tick();

	///<summary>Send error message</summary>
	///<param name="c">Message</param>
	static void Err(string c);
	///<summary>Send info message</summary>
	///<param name="c">Message</param>
	static void Info(string c);
};
Console* g_Console();

#endif