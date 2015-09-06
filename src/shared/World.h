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

	///<summary>Tick the component(graphics thread)</summary>
	void Tick();
	///<summary>Second(physics) thread</summary>
	void AsyncTick();

	///<summary>Loads the map</summary>
	///<param name="name">Filename in data/maps folder</param>
	bool Load(std::string name);
	void UnLoad();
	///<summary>Returns tile by point</summary>
	///<param name="pos">Coords of point</param>
	Tile* GetTile(glm::vec3 pos);
	///<summary>Returns null if no colision, Tile otherwise</summary>
	///<param name="pos0">start point</param>
	///<param name="pos1">end point</param>
	///<param name="pOutCollision">colision point</param>
	///<param name="pOutBeforeCollision">last point before colision</param>
	Tile* IntersectLine(glm::vec3 Pos0, glm::vec3 Pos1, glm::vec3 *pOutCollision, glm::vec3 *pOutBeforeCollision);
	void MovePoint(glm::vec3 *pInoutPos, glm::vec3 *pInoutVel, float Elasticity, int *pBounces);
	bool TestBox(glm::vec3 Pos, glm::vec3 Size);
	void MoveBox(glm::vec3 *pInoutPos, glm::vec3 *pInoutVel, glm::vec3 Size, float Elasticity);
	Player* IntersectPlayer(glm::vec3 Pos0, glm::vec3 Pos1, glm::vec3 *pOutCollision, glm::vec3 *pOutBeforeCollision, int except, float radius);
	
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