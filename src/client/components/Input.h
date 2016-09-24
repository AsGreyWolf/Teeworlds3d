#ifndef INPUT_H
#define INPUT_H

#include "../ClientComponent.h"
#include <unordered_map>
#include <vector>

class Input : public ClientComponent {
private:
	Input();
	friend Input *g_Input();

public:
	~Input() override;
	void Tick() override;
	std::unordered_map<unsigned int, char>
	    keyboard; // TODO: performance tweak, map is slow
	std::vector<char> mouse;
	bool quit;
	int mouseX;
	int mouseY;
	int mouseWheel;
};
Input *g_Input();

#endif
