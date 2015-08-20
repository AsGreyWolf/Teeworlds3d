#ifndef CONSOLE_H
#define CONSOLE_H

#include "SharedComponent.h"
#include <string>

///<summary>Text I/O interaction with player</summary>
class Console : public SharedComponent{
public:
	Console();
	~Console();

	///<summary>Tick the component(graphics thread)</summary>
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