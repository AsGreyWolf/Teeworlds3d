#ifndef WORLD_H
#define WORLD_H

#include "../component.h"

#include <array>
#include <set>
#include <shared/world/player.h>
#include <shared/world/projectile.h>
#include <shared/world/tile.h>
#include <string>
#include <tools/protocol.h>
#include <tools/vmath.h>

namespace tee3d {
namespace shared {
class world_component : public component {
private:
	world_component();

public:
	~world_component() override;

	// 	void Load(const std::string &name);
	// 	void UnLoad();
	// 	void Spawn(const Projectile &proj);
	// 	int Spawn(const Player &player);
	// 	bool isValid() const;
	// 	Tile *GetTile(const glm::vec3 &pos) const;
	// 	Tile *GetTile(int x, int y, int z) const;
	// 	Tile *IntersectLine(const glm::vec3 &pos0, const glm::vec3 &pos1,
	// 	                    glm::vec3 *collision, glm::vec3 *beforeCollision)
	// const;
	// 	void MovePoint(glm::vec3 *position, glm::vec3 *velocity, float elasticity,
	// 	               int *bounces) const;
	// 	bool TestBox(const glm::vec3 &pos, const glm::vec3 &size) const;
	// 	void MoveBox(glm::vec3 *position, glm::vec3 *velocity, const glm::vec3
	// &size,
	// 	             float elasticity) const;
	// 	const Player *IntersectPlayer(const glm::vec3 &pos0, const glm::vec3 &pos1,
	// 	                              glm::vec3 *collision, glm::vec3
	// *beforeCollision,
	// 	                              int except, float radius) const;
	//
	// 	glm::uvec3 worldSize;
	// 	std::string tileset;
	// 	std::vector<Tile> tilesById;
	// 	std::vector<Player> players;
	// 	std::vector<Projectile> projectiles;
	//
	// private:
	// 	std::vector<std::vector<std::vector<Tile *>>> tilesByPos;
};
using world = component::wrapper<world_component>;
};
};

#endif
