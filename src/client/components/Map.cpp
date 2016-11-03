#include "Map.h"
#include <client/components/ImageLoader.h>
#include <client/components/Loading.h>
#include <client/components/Resources.h>
#include <client/components/graphics/geometry/Primitives.h>
#include <shared/World.h>
#include <shared/world/Projectile.h>
#include <shared/world/Tile.h>
#include <tools/Protocol.h>

class Map *pMap;
Map *g_Map() { return pMap != nullptr ? pMap : new Map(); }

Map::Map() : ClientComponent() { pMap = this; }
Map::~Map() {
	playerModels.clear();
	pMap = nullptr;
}
void Map::Tick() {
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (g_World()->players[i]) {
			if (!playerModels[i].isEnabled()) {
				playerModels[i].Enable();
			}
			playerModels[i].Sync(g_World()->players[i]);
			playerModels[i].UpdateMatrix();
		} else if (playerModels[i].isEnabled()) {
			playerModels[i].Disable();
		}
	}
	for (size_t i = 0;
	     i < std::min(g_World()->projectiles.size(), projectileModels.size());
	     i++) {
		if (g_World()->projectiles[i]) {
			projectileModels[i].pos = g_World()->projectiles[i].pos;
			projectileModels[i].UpdateMatrix();
			projectileModels[i].Enable();
		} else {
			projectileModels[i].Disable();
		}
	}
	for (size_t i = g_World()->projectiles.size(); i < projectileModels.size();
	     i++) {
		projectileModels[i].Disable();
	}
}
bool Map::Load(const std::string &name) {
	g_World()->Load(name);
	if (!g_World()->isValid()) {
		return false;
	}

	g_Loading()->Push([&]() {
		terrain.texture =
		    g_ImageLoader()->Load("mapres/" + g_World()->tileset + ".png");
		for (Tile &buffer : g_World()->tilesById) {
			if (!buffer.isVisible()) {
				continue;
			}
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
		terrain.Enable();
		terrain.UpdateMatrix();
	});
	playerModels.resize(MAX_PLAYERS, blankPlayer);
	projectileModels.resize(256, g_Resources()->coordsModel); // TODO: why 256?
	return true;
}
void Map::UnLoad() {
	terrain = Model3d();
	playerModels.clear();
}
