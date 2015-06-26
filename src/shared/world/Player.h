#ifndef PLAYER_H
#define PLAYER_H
#include "../../tools/Protocol.h"
#include "../../../other/glm/glm.hpp"
#include <string>

///<summary>Player data as a world(physical) object</summary>
class Player{
public:
	Player(int id);

	void Tick();

	int id;
	///<summary>Position on map</summary>
	glm::vec3 pos;
	///<summary>Rotation(rads)</summary>
	glm::vec3 rot;
	///<summary>Velocity(speed)</summary>
	glm::vec3 vel;
	///<summary>Move acceleration(direction)</summary>
	glm::vec2 acc;

	glm::vec4 color;
	int weapon;
	int emote;

	std::string skin;
	std::string nickname;
};

#endif