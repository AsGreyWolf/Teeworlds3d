#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <tools/Positioned.h>
#include <tools/vmath.h>

class Projectile : Positioned {
public:
	Projectile(int type, int owner, const glm::vec3 &pos, const rot3 &rot,
	           int life, int damage, bool explosive, float force, int sound,
	           int weapon);
	glm::vec3 GetPos(float time);
	virtual void Reset();
	virtual void Tick();

private:
	int life;
	int owner;
	int type;
	int damage;
	int sound;
	int weapon;
	float force;
	int startTime;
	bool explosive;

	int prevTime;
};

#endif
