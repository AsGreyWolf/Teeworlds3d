#ifndef PLAYER_H
#define PLAYER_H
#include "../../tools/Protocol.h"
#include "../../../other/glm/glm.hpp"
#include <string>

///<summary>Player data as a world(physical) object</summary>
class Player{
public:
	Player(glm::uint8_t& id);

	void Tick();

	glm::uint8_t id;
	///<summary>Position on map</summary>
	glm::vec3 pos;
	///<summary>Rotation(rads)</summary>
	glm::vec3 rot;
	///<summary>Velocity(speed)</summary>
	glm::vec3 vel;
	///<summary>Move acceleration(direction)</summary>
	glm::vec2 acc;
	glm::uint8_t jumped;

	glm::vec4 color;
	glm::uint8_t weapon;
	glm::uint8_t emote;

	std::string skin;
	std::string nickname;

	const float physSize = 28.0f;

	bool grounded;

	bool jump;
	glm::vec3 look;
	bool hook;
	bool controls;
};

#endif