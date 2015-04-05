#ifndef SHAREDCOMPONENT_H
#define SHAREDCOMPONENT_H

#include <stdint.h>
using namespace std;

class SharedComponent{
public:
	SharedComponent(){};
	virtual ~SharedComponent(){};

	///<summary>Tick the component</summary>
	virtual void Tick(){};
};

#endif