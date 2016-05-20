#include "Map.h"
#include <tools/Protocol.h>
#include <shared/World.h>
#include <shared/world/Tile.h>
#include <client/components/Resources.h>
#include <client/components/graphics/geometry/Primitives.h>

class Map *pMap;
Map *g_Map() { return pMap ? pMap : new Map(); }

Map::Map() { pMap = this; }
Map::~Map() { pMap = 0; }
void Map::Tick() {
	for (int i = 0; i < MAX_PLAYERS; i++)
		if (g_World()->players && g_World()->players[i]) {
			playerModels[i].Enable();
			playerModels[i].Sync(*g_World()->players[i]);
			playerModels[i].UpdateMatrix();
		} else
			playerModels[i].Disable();
}
bool Map::Load(const std::string &name) {
	g_World()->Load(name);
	if (!g_World()->isValid())
		return false;
	terrain.texture = Texture("mapres/" + g_World()->tileset + ".png");
	for (Tile &buffer : g_World()->tilesById) {
		if (!buffer.isVisible())
			continue;
		if (!buffer.hasx) {
			terrain.Add(Quad(quad3(glm::vec3(buffer.x * 32 - 16, buffer.y * 32 - 16,
			                                 buffer.z * 32 + 16),
			                       glm::vec3(buffer.x * 32 - 16, buffer.y * 32 + 16,
			                                 buffer.z * 32 + 16),
			                       glm::vec3(buffer.x * 32 - 16, buffer.y * 32 + 16,
			                                 buffer.z * 32 - 16),
			                       glm::vec3(buffer.x * 32 - 16, buffer.y * 32 - 16,
			                                 buffer.z * 32 - 16)),
			                 glm::vec3(-1, 0, 0),
			                 g_Resources()->texturePos16[buffer.texOther]));
		}
		if (!buffer.hasX) {
			terrain.Add(Quad(quad3(glm::vec3(buffer.x * 32 + 16, buffer.y * 32 + 16,
			                                 buffer.z * 32 + 16),
			                       glm::vec3(buffer.x * 32 + 16, buffer.y * 32 - 16,
			                                 buffer.z * 32 + 16),
			                       glm::vec3(buffer.x * 32 + 16, buffer.y * 32 - 16,
			                                 buffer.z * 32 - 16),
			                       glm::vec3(buffer.x * 32 + 16, buffer.y * 32 + 16,
			                                 buffer.z * 32 - 16)),
			                 glm::vec3(1, 0, 0),
			                 g_Resources()->texturePos16[buffer.texOther]));
		}

		if (!buffer.hasy) {
			terrain.Add(Quad(quad3(glm::vec3(buffer.x * 32 + 16, buffer.y * 32 - 16,
			                                 buffer.z * 32 + 16),
			                       glm::vec3(buffer.x * 32 - 16, buffer.y * 32 - 16,
			                                 buffer.z * 32 + 16),
			                       glm::vec3(buffer.x * 32 - 16, buffer.y * 32 - 16,
			                                 buffer.z * 32 - 16),
			                       glm::vec3(buffer.x * 32 + 16, buffer.y * 32 - 16,
			                                 buffer.z * 32 - 16)),
			                 glm::vec3(0, -1, 0),
			                 g_Resources()->texturePos16[buffer.texOther]));
		}
		if (!buffer.hasY) {
			terrain.Add(Quad(quad3(glm::vec3(buffer.x * 32 - 16, buffer.y * 32 + 16,
			                                 buffer.z * 32 + 16),
			                       glm::vec3(buffer.x * 32 + 16, buffer.y * 32 + 16,
			                                 buffer.z * 32 + 16),
			                       glm::vec3(buffer.x * 32 + 16, buffer.y * 32 + 16,
			                                 buffer.z * 32 - 16),
			                       glm::vec3(buffer.x * 32 - 16, buffer.y * 32 + 16,
			                                 buffer.z * 32 - 16)),
			                 glm::vec3(0, 1, 0),
			                 g_Resources()->texturePos16[buffer.texOther]));
		}
		if (!buffer.hasZ) {
			terrain.Add(Quad(quad3(glm::vec3(buffer.x * 32 + 16, buffer.y * 32 + 16,
			                                 buffer.z * 32 + 16),
			                       glm::vec3(buffer.x * 32 - 16, buffer.y * 32 + 16,
			                                 buffer.z * 32 + 16),
			                       glm::vec3(buffer.x * 32 - 16, buffer.y * 32 - 16,
			                                 buffer.z * 32 + 16),
			                       glm::vec3(buffer.x * 32 + 16, buffer.y * 32 - 16,
			                                 buffer.z * 32 + 16)),
			                 glm::vec3(0, 0, 1),
			                 g_Resources()->texturePos16[buffer.texTop]));
		}
		if (!buffer.hasz) {
			terrain.Add(Quad(quad3(glm::vec3(buffer.x * 32 + 16, buffer.y * 32 - 16,
			                                 buffer.z * 32 - 16),
			                       glm::vec3(buffer.x * 32 - 16, buffer.y * 32 - 16,
			                                 buffer.z * 32 - 16),
			                       glm::vec3(buffer.x * 32 - 16, buffer.y * 32 + 16,
			                                 buffer.z * 32 - 16),
			                       glm::vec3(buffer.x * 32 + 16, buffer.y * 32 + 16,
			                                 buffer.z * 32 - 16)),
			                 glm::vec3(0, 0, -1),
			                 g_Resources()->texturePos16[buffer.texBottom]));
		}
	}
	playerModels.resize(MAX_PLAYERS, blankPlayer);
	terrain.Enable();
	terrain.UpdateMatrix();
	return true;
}
void Map::UnLoad() {
	terrain = Model3d();
	playerModels.clear();
}
