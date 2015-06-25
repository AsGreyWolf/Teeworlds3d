#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include "SharedComponent.h"
#include "../tools/Protocol.h"

class Player;
class Tile;

///<summary>World and all physical objects</summary>
class World : public SharedComponent{
public:
	World();
	~World();

	///<summary>Tick the component</summary>
	void Tick();

	///<summary>Loads the map</summary>
	///<param name="name">Filename in data/maps folder</param>
	bool Load(std::string name);
	void UnLoad();
	
	///<summary>Size in blocks</summary>
	glm::vec3 worldSize;
	///<summary>Vector of the tiles sorted by id</summary>
	std::vector<Tile> tilesById;
	///<summary>Array of the tiles sorted by position</summary>
	Tile**** tilesByPos;
	///<summary>Tileset</summary>
	std::string tileset;
	///<summary>Players array</summary>
	Player* players[MAX_PLAYERS];
};
World* g_World();

#endif