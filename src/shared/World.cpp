#include "World.h"
#include <iostream>
#include "../tools/Player.h"
//TODO debug
#include "../client/components/Graphics.h"
#include "../client/components/graphics/Resources.h"

class World* mp_World;
World* m_World(){ return mp_World; }

World::World(){
	mp_World = this;
	//TODO: only debug
	auto skinName = m_Graphics()->m_Resources->skinTextures.begin();
	for (int i = 0; i<MAX_PLAYERS; i++){
		players[i] = new Player();
		players[i]->pos = vec3(rand() % 2048, rand() % 2048, 70);
		players[i]->dir = vec3(rand() / (static_cast <float> (RAND_MAX / (M_PI * 2))), rand() / (static_cast <float> (RAND_MAX / (M_PI * 2))), rand() / (static_cast <float> (RAND_MAX / (M_PI * 2))));
		players[i]->dir = glm::normalize(players[i]->dir);
		players[i]->weapon = rand() % NUM_WEAPONS;
		players[i]->emote = EMOTE_NORMAL;
		players[i]->skin = (*skinName).first;
		players[i]->NickName = (*skinName).first;
		skinName++;
		if (skinName == m_Graphics()->m_Resources->skinTextures.end()) skinName = m_Graphics()->m_Resources->skinTextures.begin();
	}
};
World::~World(){
	for (int i = 0; i < MAX_PLAYERS; i++){
		delete players[i];
	}
	mp_World = 0;
};
void World::Tick(){}