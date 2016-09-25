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
protected:
	ClientComponent();

public:
	virtual ~ClientComponent() override;
	virtual void Message(int type, char *value);
	virtual void StateChange(const STATE &prevState);

	static void ClearComponents();
	static void MessageComponents(int type, char *value);
	static void StateChangeComponents(const STATE &prevState);

	static STATE state;

private:
	static std::list<ClientComponent *> registred;
};

#endif
