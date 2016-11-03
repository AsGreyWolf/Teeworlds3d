#ifndef MAP_H
#define MAP_H

#include "../ClientComponent.h"
#include <client/components/graphics/models/Model3d.h>
#include <client/components/graphics/models/PlayerModel.h>
#include <string>
#include <vector>

class Map : public ClientComponent {
private:
	Map();
	friend Map *g_Map();

public:
	~Map() override;
	void Tick() override;

	bool Load(const std::string &name);
	void UnLoad();

private:
	Model3d terrain;
	PlayerModel blankPlayer;
	std::vector<PlayerModel> playerModels;
	std::vector<Model3d> projectileModels;
};
Map *g_Map();

#endif
