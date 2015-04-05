#ifndef WORLD_H
#define WORLD_H

#include "SharedComponent.h"
#include "../tools/Protocol.h"

class Player;

class World : public SharedComponent{
public:
	World();
	~World();

	///<summary>Tick the component</summary>
	void Tick();

	///<summary>Players array</summary>
	Player* players[MAX_PLAYERS];
};
World* g_World();

#endif