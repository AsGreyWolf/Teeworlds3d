#ifndef MAP_H
#define MAP_H

#include "../ClientComponent.h"
#include <string>
#include <vector>
#include <client/components/graphics/models/Model3d.h>
#include <client/components/graphics/models/PlayerModel.h>

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
};
Map *g_Map();

#endif
