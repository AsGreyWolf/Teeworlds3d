#include "Projectile.h"
#include <shared/System.h>
#include <shared/World.h>

Projectile::Projectile(const glm::vec3 &pos, const rot3 &rot, int type,
                       int life, int owner, int damage, int weapon,
                       bool explosive, float force, int sound) {
	this->pos = pos;
	this->rot = rot;
	this->type = type;
	this->life = life;
	startTime = g_System()->GetTime();
	prevTime = startTime;

	this->owner = owner;
	// this->damage = damage;
	// this->weapon = weapon;
	// this->explosive = explosive;
	// this->force = force;
	// this->sound = sound;
}
glm::vec3 Projectile::GetPos(float time) {
	float tuningGrenadeCurvature = 7.0f;
	float tuningGrenadeSpeed = 1000.0f;
	float tuningShotgunCurvature = 1.25f;
	float tuningShotgunSpeed = 2750.0f;
	float tuningGunCurvature = 1.25f;
	float tuningGunSpeed = 2200.0f;
	float curvature = 0;
	float speed = 0;
	switch (type) {
	case WEAPON_GRENADE:
		curvature = tuningGrenadeCurvature;
		speed = tuningGrenadeSpeed;
		break;
	case WEAPON_SHOTGUN:
		curvature = tuningShotgunCurvature;
		speed = tuningShotgunSpeed;
		break;
	case WEAPON_GUN:
		curvature = tuningGunCurvature;
		speed = tuningGunSpeed;
		break;
	}
	time *= speed / 1000.0f;
	glm::vec3 n = pos + glm::rotate(glm::vec3(0, 1, 0), rot) * time;
	n.z -= curvature / 10000.0f * (time * time);
	return n;
}
void Projectile::Reset() { life = -1; }
void Projectile::Tick() {
	auto time = g_System()->GetTime();
	glm::vec3 prevPos = GetPos(prevTime - startTime);
	glm::vec3 curPos = GetPos(time - startTime);
	Tile *collide = g_World()->IntersectLine(prevPos, curPos, &curPos, nullptr);
	const Player *targetPlayer =
	    g_World()->IntersectPlayer(prevPos, curPos, &curPos, nullptr, owner, 6.0f);
	life--;
	if ((targetPlayer != nullptr) || (collide != nullptr) || life < 0) {
		// TODO:380 || GameLayerClipped(CurPos)
		// TODO:170 if (life >= 0 || weapon ==
		// WEAPON_GRENADE)GameServer()->CreateSound(CurPos, m_SoundImpact);
		// TODO:160 if (explosive) GameServer()->CreateExplosion(CurPos, m_Owner,
		// m_Weapon, false);
		// TODO:40 else if (TargetChr) TargetChr->TakeDamage(m_Direction * max(0.001f,
		// m_Force), m_Damage, m_Owner, m_Weapon);

		Reset();
	}
	pos = curPos;
	prevTime = time;
}
