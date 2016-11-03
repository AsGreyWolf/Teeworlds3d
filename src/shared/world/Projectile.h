#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <tools/Positioned.h>
#include <tools/vmath.h>

class Projectile : public Positioned {
public:
	Projectile(const glm::vec3 &pos, const rot3 &rot, int type, int life,
	           int owner, int damage, int weapon, bool explosive, float force,
	           int sound);
	glm::vec3 GetPos(float time);
	virtual void Reset();
	virtual void Tick();

	inline operator bool() const { return life > 0; }

private:
	int type;
	int life;
	int startTime;

	int owner;
	// int damage; // TODO:
	// int weapon;
	// bool explosive;
	// float force;
	// int sound;

	int prevTime;
};

#endif
