#ifndef PLAYER_H
#define PLAYER_H

#include <chrono>
#include <string>
#include <tools/performance.h>
#include <tools/positioned.h>
#include <tools/vmath.h>

namespace tee3d {
namespace shared {
using glm::vec4;
using glm::vec3;
using glm::vec2;
using std::string;
class player : public positioned {
public:
	explicit player(uint8_t id);

	const uint8_t id;
	vec3 vel;
	vec2 dir;
	uint8_t jumped;
	hook_state_t hook_state;
	vec3 hook_pos;
	vec3 hook_dir;
	player_id_t hooked_player;
	duration_t hook_start;
	// individuality
	vec4 color;
	weapon_t weapon;
	emote_t emote;
	string skin;
	string nickname;
	// calculated
	bool grounded;
	// local controls
	bool jump;
	rot3 look;
	bool hook;
	bool local;

	player &operator=(const player &p);
	bool operator==(const player &p) const { return p.id == id; }
	operator bool() const { return nickname.length() > 0; }

	const float physSize = 28.0f;

private:
	friend class world_component;
};
};
};

#endif
