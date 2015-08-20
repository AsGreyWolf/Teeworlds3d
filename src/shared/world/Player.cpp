#include "Player.h"
#include "../World.h"
#include "Tile.h"
#define GLM_FORCE_RADIANS
#include "../../../other/glm/gtx/rotate_vector.hpp"

Player::Player(int id){
	this->id = id;
	pos = glm::vec3(0, 0, 0);
	rot=glm::vec3(0,0,0);
	vel = glm::vec3(0, 0, 0);
	acc = glm::vec2(0, 0);

	color = glm::vec4(0, 0, 0, 0);
	int weapon=0;
	int emote=0;

	std::string skin="";
	std::string nickname="";
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
	float tuningVelrampCurvature = 1.4;
	bool tuningPlayerColision = true;
	float PhysSize = 28.0f;

	bool Grounded = false;
	Tile* buf = g_World()->GetTile(glm::vec3(pos.x + PhysSize / 2, pos.y + PhysSize / 2, pos.z - PhysSize / 2 - 5));
	if (buf && buf->isPhys())
		Grounded = true;
	buf = g_World()->GetTile(glm::vec3(pos.x + PhysSize / 2, pos.y - PhysSize / 2, pos.z - PhysSize / 2 - 5));
	if (buf && buf->isPhys())
		Grounded = true;
	buf = g_World()->GetTile(glm::vec3(pos.x - PhysSize / 2, pos.y + PhysSize / 2, pos.z - PhysSize / 2 - 5));
	if (buf && buf->isPhys())
		Grounded = true;
	buf = g_World()->GetTile(glm::vec3(pos.x - PhysSize / 2, pos.y - PhysSize / 2, pos.z - PhysSize / 2 - 5));
	if (buf && buf->isPhys())
		Grounded = true;
	glm::vec3 TargetDirection(0, 1, 0);
	TargetDirection = glm::rotateZ(TargetDirection, rot.z);
	TargetDirection = glm::rotateX(TargetDirection, rot.x);
	TargetDirection = glm::rotateY(TargetDirection, rot.y);

	vel.z -= tuningGravity;
	float MaxSpeed = Grounded ? tuningGroundSpeed : tuningAirSpeed;
	float Accel = Grounded ? tuningGroundAccel : tuningAirAccel;
	float Friction = Grounded ? tuningGroundFriction : tuningAirFriction;


	float RampValue = VelocityRamp(glm::length(vel) * 50, tuningVelrampStart, tuningVelrampRange, tuningVelrampCurvature);
	vel.x = vel.x*RampValue;
	vel.y = vel.y*RampValue;
	glm::vec3 NewPos = pos;
	g_World()->MoveBox(&NewPos, &vel, glm::vec3(PhysSize, PhysSize, PhysSize), 0);
	vel.x = vel.x*(1.0f / RampValue);
	vel.y = vel.y*(1.0f / RampValue);
	if (tuningPlayerColision)
	{
		glm::vec3 collidePos;
		if(g_World()->IntersectPlayer(pos, NewPos, NULL, &collidePos, id)!=NULL)
			NewPos = collidePos;
	}
	pos = NewPos;
}