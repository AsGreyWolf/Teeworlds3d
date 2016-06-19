#ifndef COMPONENT_H
#define COMPONENT_H

#include "../shared/SharedComponent.h"

#include <SDL.h>

///<summary>Client state</summary>
struct STATE {
	inline bool operator!=(const STATE s) const { return ingame != s.ingame; }
	bool ingame = false;
};
///<summary>Component which may be used only on Client side</summary>
class ClientComponent : public SharedComponent {
public:
	ClientComponent();
	virtual ~ClientComponent();
	virtual void Message(int type, char *value);
	virtual void StateChange(const STATE &lastState);

	static void ClearComponents();
	static void MessageComponents(int type, char *value);
	static void StateChangeComponents(const STATE &lastState);

	static STATE state;

private:
	static std::list<ClientComponent *> registred;
};

#endif
