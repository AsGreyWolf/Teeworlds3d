#include "World.h"
#include <iostream>
#include "world/Player.h"
//TODO debug
#include "../client/components/Graphics.h"
#include "../client/components/graphics/Resources.h"//TODO: REMOVE IT, NOW!

class World* pWorld;
World* g_World(){ return pWorld; }

World::World(){
	pWorld = this;
	//TODO: only debug
	auto skinName = g_Graphics()->m_Resources->skinTextures.begin();
	for (int i = 0; i<MAX_PLAYERS; i++){
		players[i] = new Player(i);
		players[i]->pos = vec3(rand() % 2048, rand() % 2048, rand() % 2048);
		players[i]->rot = vec3(rand() / (static_cast <float> (RAND_MAX / (M_PI * 2))), rand() / (static_cast <float> (RAND_MAX / (M_PI * 2))), rand() / (static_cast <float> (RAND_MAX / (M_PI * 2))));
		players[i]->rot = glm::normalize(players[i]->rot);
		players[i]->weapon = rand() % NUM_WEAPONS;
		players[i]->emote = EMOTE_NORMAL;
		players[i]->skin = (*skinName).first;
		players[i]->nickname = (*skinName).first;
		skinName++;
		if (skinName == g_Graphics()->m_Resources->skinTextures.end()) skinName = g_Graphics()->m_Resources->skinTextures.begin();
	}
};
World::~World(){
	for (int i = 0; i < MAX_PLAYERS; i++){
		delete players[i];
	}
	pWorld = 0;
};
void World::Tick(){}