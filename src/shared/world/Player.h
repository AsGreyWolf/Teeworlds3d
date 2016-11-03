#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <tools/Positioned.h>
#include <tools/Protocol.h>
#include <tools/vmath.h>

///<summary>Player data as a world(physical) object</summary>
class Player : public Positioned {
public:
	explicit Player(glm::uint8_t id);

	void Tick();

	const glm::uint8_t id;
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
	// individuality
	glm::vec4 color;
	glm::uint8_t weapon;
	glm::uint8_t emote;
	std::string skin;
	std::string nickname;
	// calculated
	bool grounded;
	// local controls
	bool jump;
	rot3 look;
	bool hook;
	bool local;

	Player &operator=(const Player &p);
	bool operator==(const Player &p) const { return p.id == id; }
	operator bool() const { return nickname.length() > 0; }

	const float physSize = 28.0f;

private:
	friend class World;
};

#endif
