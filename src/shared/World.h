#ifndef WORLD_H
#define WORLD_H

#include "SharedComponent.h"

#include <string>
#include <vector>
#include <tools/vmath.h>
#include <tools/Protocol.h>

class Player;
class Tile;

///<summary>World and all physical objects</summary>
class World : public SharedComponent {
private:
	World();
	friend World *g_World();

public:
	~World() override;

	///<summary>Tick the component(graphics thread)</summary>
	void Tick() override;

	///<summary>Loads the map</summary>
	///<param name="name">Filename in data/maps folder</param>
	void Load(const std::string &name);
	void UnLoad();
	bool isValid() const;
	///<summary>Returns tile by point</summary>
	///<param name="pos">Coords of point</param>
	Tile *GetTile(const glm::vec3 &pos) const;
	///<summary>Returns tile by  coords</summary>
	///<param name="x">X coord</param>
	///<param name="y">Y coord</param>
	///<param name="z">Z coord</param>
	Tile *GetTile(int x, int y, int z) const;
	///<summary>Returns null if no collision, Tile otherwise</summary>
	///<param name="pos0">start point</param>
	///<param name="pos1">end point</param>
	///<param name="collision">colision point</param>
	///<param name="beforeCollision">last point before colision</param>
	Tile *IntersectLine(const glm::vec3 &pos0, const glm::vec3 &pos1,
	                    glm::vec3 *collision, glm::vec3 *beforeCollision) const;
	void MovePoint(glm::vec3 *pos, glm::vec3 *vel, float elasticity,
	               int *bounces) const;
	bool TestBox(const glm::vec3 &pos, const glm::vec3 &size) const;
	void MoveBox(glm::vec3 *pos, glm::vec3 *vel, const glm::vec3 &size,
	             float elasticity) const;
	Player *IntersectPlayer(const glm::vec3 &pos0, const glm::vec3 &pos1,
	                        glm::vec3 *collision, glm::vec3 *beforeCollision,
	                        int except, float radius) const;

	///<summary>Size in blocks</summary>
	glm::uvec3 worldSize;
	///<summary>Tileset</summary>
	std::string tileset;
	///<summary>Vector of the tiles sorted by id</summary>
	std::vector<Tile> tilesById;
	///<summary>Players array</summary>
	Player *players[MAX_PLAYERS];

private:
	///<summary>Array of the tiles sorted by position</summary>
	Tile ****tilesByPos;
};
World *g_World();

#endif
