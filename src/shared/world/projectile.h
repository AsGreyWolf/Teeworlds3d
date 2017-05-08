#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <tools/performance.h>
#include <tools/positioned.h>
#include <tools/vmath.h>

namespace tee3d {
namespace shared {
using glm::vec3;
class projectile : public positioned {
public:
	projectile(const vec3 &pos, const rot3 &rot, weapon_t type, duration_t life,
	           player_id_t owner, int damage, weapon_t weapon, bool explosive,
	           float force, sound_t sound);

	inline operator bool() const { return life.count() > 0; }

private:
	weapon_t type;
	duration_t life;
	duration_t start_time;

	int owner;
	// int damage; // TODO:
	// weapon_t weapon;
	// bool explosive;
	// float force;
	// sound_t sound;

	duration_t prev_time;

	friend class world_component;
};
};
};

#endif
