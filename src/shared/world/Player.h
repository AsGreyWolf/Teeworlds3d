#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <tools/Protocol.h>
#include <tools/vmath.h>
#include <shared/world/Positioned.h>

///<summary>Player data as a world(physical) object</summary>
class Player : public Positioned {
public:
	Player(glm::uint8_t id);

	void Tick();

	glm::uint8_t id;
	///<summary>Velocity(speed)</summary>
	glm::vec3 vel;
	///<summary>Move acceleration(direction)</summary>
	glm::vec2 dir;
	///<summary>Jump state</summary>
	glm::uint8_t jumped;
	///<summary>Hook state</summary>
	glm::int8_t hookState;
	///<summary>Hook position</summary>
	glm::vec3 hookPos;
	///<summary>Hook direction</summary>
	glm::vec3 hookDir;
	///<summary>Hooked player</summary>
	glm::int16_t hookedPlayer;
	///<summary>Hook fly start time</summary>
	long hookTime;

	glm::vec4 color;
	glm::uint8_t weapon;
	glm::uint8_t emote;
	std::string skin;
	std::string nickname;

	const float physSize = 28.0f;

	bool grounded;

	bool jump;
	rot3 look;
	bool hook;
	bool local;

	bool operator==(Player *p) const { return p->id == id; }
};

#endif
