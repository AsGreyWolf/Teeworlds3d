#ifndef SHAREDCOMPONENT_H
#define SHAREDCOMPONENT_H

#include <stdint.h>
#include <list>
using namespace std;

///<summary>Component which may be used on both(Client/Server) sides</summary>
class SharedComponent{
public:
	SharedComponent();
	virtual ~SharedComponent();

	///<summary>Tick the component</summary>
	virtual void Tick();

	static void RegisterComponent(SharedComponent* component);
	static void UnRegisterComponent(SharedComponent* component);
	static void ClearComponents();
	static void TickComponents();
private:
	static std::list <SharedComponent*> registredSharedComponents;
};

#endif