#include "Projectile.h"
#include <shared/System.h>
#include <shared/World.h>

Projectile::Projectile(int type, int owner, const glm::vec3 &pos,
                       const glm::vec3 &rot, int life, int damage,
                       bool explosive, float force, int sound, int weapon) {
	this->type = type;
	this->owner = owner;
	this->pos = pos;
	this->rot = rot;
	this->life = life;
	this->damage = damage;
	this->explosive = explosive;
	this->force = force;
	this->sound = sound;
	this->weapon = weapon;
	startTime = g_System()->GetTime();
	lastTime = startTime;
	g_World()->projectiles.push_back(this);
}
glm::vec3 Projectile::GetPos(float time) {
	float tuningGrenadeCurvature = 1.5f;
	float tuningGrenadeSpeed = 1.5f;
	float tuningShotgunCurvature = 1.5f;
	float tuningShotgunSpeed = 1.5f;
	float tuningGunCurvature = 1.5f;
	float tuningGunSpeed = 1.5f;
	float Curvature = 0;
	float Speed = 0;
	switch (type) {
	case WEAPON_GRENADE:
		Curvature = tuningGrenadeCurvature;
		Speed = tuningGrenadeSpeed;
		break;

	case WEAPON_SHOTGUN:
		Curvature = tuningShotgunCurvature;
		Speed = tuningShotgunSpeed;
		break;

	case WEAPON_GUN:
		Curvature = tuningGunCurvature;
		Speed = tuningGunSpeed;
		break;
	}
	glm::vec3 n = pos + glm::rotate(glm::vec3(0, 1, 0), rot) * time;
	n.z -= Curvature / 10000 * (time * time);
	return n;
}
void Projectile::Reset() {
	std::remove(g_World()->projectiles.begin(), g_World()->projectiles.end(),
	            this);
}
void Projectile::Tick() {
	float Pt = lastTime - startTime;
	float Ct = g_System()->GetTime() - startTime;
	glm::vec3 PrevPos = GetPos(Pt);
	glm::vec3 CurPos = GetPos(Ct);
	Tile *collide = g_World()->IntersectLine(PrevPos, CurPos, &CurPos, 0);
	Player *targetPlayer =
	    g_World()->IntersectPlayer(PrevPos, CurPos, &CurPos, 0, owner, 6.0f);
	life--;
	if (targetPlayer || collide || life < 0) { // TODO: || GameLayerClipped(CurPos)
		// if (life >= 0 || weapon == WEAPON_GRENADE)
		// TODO: GameServer()->CreateSound(CurPos, m_SoundImpact);

		// if (explosive)
		// TODO: GameServer()->CreateExplosion(CurPos, m_Owner, m_Weapon, false);

		// TODO: else if (TargetChr) TargetChr->TakeDamage(m_Direction * max(0.001f,
		// m_Force),
		//                                          m_Damage, m_Owner, m_Weapon);

		Reset();
	}
}
