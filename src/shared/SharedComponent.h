#ifndef SHAREDCOMPONENT_H
#define SHAREDCOMPONENT_H

#include <stdint.h>
using namespace std;

///<summary>Component which may be used on both(Client/Server) sides</summary>
class SharedComponent{
public:
	SharedComponent(){};
	virtual ~SharedComponent(){};

	///<summary>Tick the component</summary>
	virtual void Tick(){};
};

#endif