#ifndef SHAREDCOMPONENT_H
#define SHAREDCOMPONENT_H

#include <list>
#include <stdint.h>
#ifdef __ANDROID__
#include <tools/android.h> // NDK fix
#endif

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
