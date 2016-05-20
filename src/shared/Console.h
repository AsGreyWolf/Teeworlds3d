#ifndef CONSOLE_H
#define CONSOLE_H

#include "SharedComponent.h"

#include <string>

///<summary>Text I/O interaction with player</summary>
class Console : public SharedComponent {
private:
	Console();
	friend Console *g_Console();

public:
	~Console() override;

	///<summary>Send error message</summary>
	///<param name="c">Message</param>
	void Err(const std::string &c);
	///<summary>Send info message</summary>
	///<param name="c">Message</param>
	void Info(const std::string &c);
};
Console *g_Console();

#endif
