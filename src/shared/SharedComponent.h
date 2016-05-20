#ifndef SHAREDCOMPONENT_H
#define SHAREDCOMPONENT_H

#include <stdint.h>
#include <list>

class SharedComponent {
public:
	SharedComponent();
	virtual ~SharedComponent();

	virtual void Tick();

	static void ClearComponents();
	static void TickComponents();

private:
	static std::list<SharedComponent *> registred;
};

#endif
