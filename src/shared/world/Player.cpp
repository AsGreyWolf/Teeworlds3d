#include "Player.h"
#include "../World.h"
#include "../System.h"
#include "Tile.h"
#define GLM_FORCE_RADIANS
#include "../../../other/glm/gtx/rotate_vector.hpp"

Player::Player(glm::uint8_t& id){
	this->id = id;
	pos = glm::vec3(0, 0, 0);
	rot = glm::vec3(0,0,0);
	vel = glm::vec3(0, 0, 0);
	acc = glm::vec2(0, 0);
	jumped = 0;

	color = glm::vec4(1, 1, 1, 0);
	weapon=0;
	emote=0;

	std::string skin="";
	std::string nickname="";

	grounded = true;

	controls = false;
};
float VelocityRamp(float Value, float Start, float Range, float Curvature)
{
	if (Value < Start)
		return 1.0f;
	return 1.0f / powf(Curvature, (Value - Start) / Range);
}
void Player::Tick(){
	float tuningGravity = 0.5f;
	float tuningGroundSpeed = 10.0f;
	float tuningAirSpeed = 5.0f;
	float tuningGroundAccel = 2.0f;
	float tuningAirAccel = 1.5f;
	float tuningGroundFriction = 0.5f;
	float tuningAirFriction = 0.95f;
	float tuningVelrampStart = 550;
	float tuningVelrampRange = 2000;
	float tuningVelrampCurvature = 1.4f;
	bool tuningPlayerColision = true;
	float tuningGroundJumpImpulse = 13.2f;
	float tuningAirJumpImpulse = 12.0f;

	float coeff = (float)(g_System()->tickCoeff * 60);

	grounded = false;
	Tile* buf = g_World()->GetTile(glm::vec3(pos.x + physSize / 2, pos.y + physSize / 2, pos.z - physSize / 2 - 5));
	if (buf && buf->isPhys())
		grounded = true;
	buf = g_World()->GetTile(glm::vec3(pos.x + physSize / 2, pos.y - physSize / 2, pos.z - physSize / 2 - 5));
	if (buf && buf->isPhys())
		grounded = true;
	buf = g_World()->GetTile(glm::vec3(pos.x - physSize / 2, pos.y + physSize / 2, pos.z - physSize / 2 - 5));
	if (buf && buf->isPhys())
		grounded = true;
	buf = g_World()->GetTile(glm::vec3(pos.x - physSize / 2, pos.y - physSize / 2, pos.z - physSize / 2 - 5));
	if (buf && buf->isPhys())
		grounded = true;

	vel.z -= coeff*tuningGravity;
	float MaxSpeed = grounded ? tuningGroundSpeed : tuningAirSpeed;
	float Accel = grounded ? tuningGroundAccel : tuningAirAccel;
	float Friction = grounded ? tuningGroundFriction : tuningAirFriction;

	if(controls){
		rot = look;
		if (jump)
		{
			if (!(jumped & 1))
			{
				if (grounded)
				{
					vel.z = tuningGroundJumpImpulse;
					jumped |= 1;
				}
				else if (!(jumped & 2))
				{
					vel.z = tuningAirJumpImpulse;
					jumped |= 3;
				}
			}
		}
		else
			jumped &= ~1;
		//TODO: hook
	}
	{
		glm::vec2 nvel(vel.x, vel.y);
		if (glm::length(acc)==0.0f)
			nvel *= pow(Friction,coeff);
		else {
			nvel += coeff*acc*Accel;
			if (glm::length(nvel) > MaxSpeed)
				nvel = glm::normalize(nvel)*MaxSpeed;
		}
		vel.x = nvel.x;
		vel.y = nvel.y;
	}
	if (grounded)
		jumped &= ~2;
	//TODO: HOOK
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (i == id) continue;
		Player* p = g_World()->players[i];
		float distance = glm::distance(pos, p->pos);
		glm::vec3 dir = glm::normalize(pos - p->pos);
		if (tuningPlayerColision && distance < physSize*1.25f && distance > 0.0f)
		{
			float a = (physSize*1.45f - distance);
			float velocity = 0.5f;

			// make sure that we don't add excess force by checking the
			// direction against the current velocity. if not zero.
			if (glm::length(vel) > 0.0001)
				velocity = 1 - (glm::dot(glm::normalize(vel), dir) + 1) / 2;

			vel += coeff*dir*a*(velocity*0.75f);
			vel *= pow(0.85f,coeff);
		}
		//TODO: HOOK
	}
	if (glm::length(vel) > 6000.0f)
		vel = glm::normalize(vel) * 6000.0f;
	


	float RampValue = VelocityRamp(glm::length(vel) * 50, tuningVelrampStart, tuningVelrampRange, tuningVelrampCurvature);
	vel.x = vel.x*RampValue;
	vel.y = vel.y*RampValue;
	glm::vec3 NewPos = pos;
	g_World()->MoveBox(&NewPos, &vel, glm::vec3(physSize, physSize, physSize), 0);
	vel.x = vel.x*(1.0f / RampValue);
	vel.y = vel.y*(1.0f / RampValue);
	if (tuningPlayerColision)
	{
		glm::vec3 collidePos;
		if(g_World()->IntersectPlayer(pos, NewPos, NULL, &collidePos, id, physSize / 2)!=NULL)
			NewPos = collidePos;
	}
	pos = NewPos;
	if (pos.z < -6000) pos = glm::vec3(100,100,6000);
}