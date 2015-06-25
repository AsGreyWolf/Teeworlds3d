#include "World.h"
#include <iostream>
#include "world/Player.h"
#include "world/Tile.h"
#include "Console.h"
#include "System.h"
//TODO debug
#include "../client/components/Graphics.h"
#include "../client/components/graphics/Resources.h"//TODO: REMOVE IT, NOW!

class World* pWorld;
World* g_World(){ return pWorld; }

World::World(){
	pWorld = this;
	UnLoad();
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
	UnLoad();
	pWorld = 0;
};
void World::Tick(){}
bool World::Load(string name){
	string pp = "maps/" + name + ".map";
	string path = g_System()->GetDataFile(pp);

	Console::Info("Loading " + name);

	FILE* file = fopen(path.c_str(), "rb");
	if (file == 0){
		Console::Err("File not found");
		return false;
	}
	unsigned char buf;
	buf = fgetc(file);
	worldSize.x = (int)(buf);
	buf = fgetc(file);
	worldSize.y = (int)(buf);
	buf = fgetc(file);
	worldSize.z = (int)(buf);

	tilesById.clear();
	tilesByPos = new Tile***[(int)worldSize.x];

	unsigned int i = 0;
	for (int xi = 0; xi<worldSize.x; xi++){
		tilesByPos[xi] = new Tile**[(int)worldSize.y];
		for (int yi = 0; yi<worldSize.y; yi++){
			tilesByPos[xi][yi] = new Tile*[(int)worldSize.z];
			for (int zi = 0; zi<worldSize.z; zi++){
				Tile tile;
				tilesById.push_back(tile);
				tilesById[i].id = i;
				tilesById[i].x = xi;
				tilesById[i].y = yi;
				tilesById[i].z = zi;
				buf = fgetc(file);
				tilesById[i].type = (int)(buf);
				buf = fgetc(file);
				tilesById[i].texTop = (int)(buf);
				buf = fgetc(file);
				tilesById[i].texBottom = (int)(buf);
				buf = fgetc(file);
				tilesById[i].texOther = (int)(buf);
				i++;
			}
		}
	}
	for (i = 0; i<tilesById.size(); i++){
		tilesByPos[tilesById[i].x][tilesById[i].y][tilesById[i].z] = &tilesById[i];
	}
	char s[50];
	fgets(s, sizeof(s), file);
	for (int j = 0; j<50; j++){
		if (s[j] == '\n') {
			s[j] = '\0';
			break;
		}
	}
	tileset = string(s);
	return true;
}
void World::UnLoad(){
	tilesById.clear();
	for (int xi = 0; xi<worldSize.x; xi++){
		for (int yi = 0; yi<worldSize.y; yi++)
			delete[] tilesByPos[xi][yi];
		delete[] tilesByPos[xi];
	}
	worldSize = glm::vec3(0, 0, 0);
	tileset = "";
}