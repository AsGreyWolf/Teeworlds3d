#include "Player.h"

#include <shared/System.h>
#include <shared/World.h>
#include <shared/world/Tile.h>

Player::Player(glm::uint8_t id) {
	this->id = id;
	pos = glm::vec3(0, 0, 0);
	rot = rot3(glm::vec3(0, 1, 0));
	vel = glm::vec3(0, 0, 0);
	dir = glm::vec2(0, 0);
	jumped = 0;
	hookState = HOOK_IDLE;
	hookPos = glm::vec3(0, 0, 0);
	hookDir = glm::vec3(0, 0, 0);
	hookedPlayer = -1;

	color = glm::vec4(1, 1, 1, 0);
	weapon = 0;
	emote = 0;

	std::string skin = "";
	std::string nickname = "";

	grounded = true;

	local = false;
};
float VelocityRamp(float value, float start, float range, float curvature) {
	if (value < start) {
		return 1.0f;
	}
	return 1.0f / pow(curvature, (value - start) / range);
}
void Player::Tick() {
	float tuningGravity = 0.5f; // TODO: tuning
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
	float tuningHookLength = 380.0f;
	float tuningHookFireSpeed = 80.0f;
	float tuningHookDragAccel = 3.0f;
	float tuningHookDragSpeed = 15.0f;
	bool tuningPlayerHooking = true;

	long time = g_System()->GetTime();

	World *world = g_World();

	grounded = false;
	Tile *buf = world->GetTile(glm::vec3(
	    pos.x + physSize / 2, pos.y + physSize / 2, pos.z - physSize / 2 - 5));
	if (buf != nullptr && buf->isPhys()) {
		grounded = true;
	}
	buf = world->GetTile(glm::vec3(pos.x + physSize / 2, pos.y - physSize / 2,
	                               pos.z - physSize / 2 - 5));
	if (buf != nullptr && buf->isPhys()) {
		grounded = true;
	}
	buf = world->GetTile(glm::vec3(pos.x - physSize / 2, pos.y + physSize / 2,
	                               pos.z - physSize / 2 - 5));
	if (buf != nullptr && buf->isPhys()) {
		grounded = true;
	}
	buf = world->GetTile(glm::vec3(pos.x - physSize / 2, pos.y - physSize / 2,
	                               pos.z - physSize / 2 - 5));
	if (buf != nullptr && buf->isPhys()) {
		grounded = true;
	}
	vel.z -= tuningGravity;
	float MaxSpeed = grounded ? tuningGroundSpeed : tuningAirSpeed;
	float Accel = grounded ? tuningGroundAccel : tuningAirAccel;
	float Friction = grounded ? tuningGroundFriction : tuningAirFriction;

	if (local) {
		rot = look;
		if (jump) {
			if ((jumped & 1) == 0) {
				if (grounded) {
					vel.z = tuningGroundJumpImpulse;
					jumped |= 1;
				} else if ((jumped & 2) == 0) {
					vel.z = tuningAirJumpImpulse;
					jumped |= 3;
				}
			}
		} else {
			jumped &= ~1;
		}
		if (hook) {
			if (hookState == HOOK_IDLE) {
				hookState = HOOK_FLYING;
				hookDir = glm::rotate(glm::vec3(0, 1, 0), look);
				hookPos = pos + hookDir * physSize * 1.5f;
				hookedPlayer = -1;
				hookTime = time;
			}
		} else {
			hookedPlayer = -1;
			hookState = HOOK_IDLE;
			hookPos = pos;
		}
	}
	{
		glm::vec2 nvel(vel.x, vel.y);
		if (glm::zero(dir)) {
			nvel *= Friction;
		} else {
			nvel += dir * Accel;
			if (glm::length(nvel) > MaxSpeed) {
				nvel = glm::normalize(nvel) * MaxSpeed;
			}
		}
		vel.x = nvel.x;
		vel.y = nvel.y;
	}
	if (grounded) {
		jumped &= ~2;
	}
	if (hookState == HOOK_IDLE) {
		hookedPlayer = -1;
		hookState = HOOK_IDLE;
		hookPos = pos;
	} else if (hookState >= HOOK_RETRACT_START && hookState < HOOK_RETRACT_END) {
		hookState++;
	} else if (hookState == HOOK_RETRACT_END) {
		hookState = HOOK_RETRACTED;
	} else if (hookState == HOOK_FLYING) {
		glm::vec3 newPos = hookPos + hookDir * tuningHookFireSpeed;
		if (glm::distance(pos, newPos) > tuningHookLength) {
			hookState = HOOK_RETRACT_START;
			newPos = pos + glm::normalize(newPos - pos) * tuningHookLength;
		}
		bool goingToHitGround = false;
		bool goingToRetract = false;
		Tile *hit = world->IntersectLine(hookPos, newPos, &newPos, nullptr);
		if ((hit != nullptr) && hit->isPhys()) {
			if (hit->isNoHook()) {
				goingToRetract = true;
			} else {
				goingToHitGround = true;
			}
		}
		if (tuningPlayerHooking) {
			float distance = 0.0f;
			for (auto player : world->players) {
				if (player == this) {
					continue;
				}
				glm::vec3 closestPoint =
				    glm::closestPointOnLine(hookPos, newPos, player->pos);
				if (glm::distance(player->pos, closestPoint) < physSize + 2.0f) {
					if (hookedPlayer == -1 || glm::distance(hookPos, player->pos) < distance) {
						hookState = HOOK_GRABBED;
						hookedPlayer = player->id;
						distance = glm::distance(hookPos, player->pos);
					}
				}
			}
		}
		if (hookState == HOOK_FLYING) {
			if (goingToHitGround) {
				hookState = HOOK_GRABBED;
			} else if (goingToRetract) {
				hookState = HOOK_RETRACT_START;
			}

			hookPos = newPos;
		}
	}
	if (hookState == HOOK_GRABBED) {
		if (hookedPlayer != -1) {
			Player *player = world->players.at(hookedPlayer);
			if (player != nullptr) {
				hookPos = player->pos;
			} else {
				hookedPlayer = -1;
				hookState = HOOK_RETRACTED;
				hookPos = pos;
			}
		}
		if (hookedPlayer == -1 && glm::distance(hookPos, pos) > 46.0f) {
			glm::vec3 hookVel = glm::normalize(hookPos - pos) * tuningHookDragAccel;
			if (hookVel.z < 0) {
				hookVel.z *= 0.3f;
			}
			if ((hookVel.x < 0 && dir.x < 0) || (hookVel.x > 0 && dir.x > 0)) {
				hookVel.x *= 0.95f;
			} else {
				hookVel.x *= 0.75f;
			}
			if ((hookVel.y < 0 && dir.y < 0) || (hookVel.y > 0 && dir.y > 0)) {
				hookVel.y *= 0.95f;
			} else {
				hookVel.y *= 0.75f;
			}
			glm::vec3 newVel = vel + hookVel;
			if (glm::length(newVel) < tuningHookDragSpeed ||
			    glm::length(newVel) < glm::length(vel)) {
				vel = newVel;
			}
		}
		if (hookedPlayer != -1 && (time - hookTime > 1250 ||
		                           (world->players.at(hookedPlayer) == nullptr))) {
			hookedPlayer = -1;
			hookState = HOOK_RETRACTED;
			hookPos = pos;
		}
	}
	for (auto player : world->players) { // TODO: clipping
		if (player == this || (player == nullptr)) {
			continue;
		}
		float distance = glm::distance(pos, player->pos);
		if (tuningPlayerColision && distance < physSize * 1.25f && distance > 0.0f) {
			glm::vec3 dir = glm::normalize(pos - player->pos);
			float a = (physSize * 1.45f - distance);
			float velocity = 0.5f;
			if (!glm::zero(vel)) {
				velocity = 1 - (glm::dot(glm::normalize(vel), dir) + 1) / 2;
			}
			vel += dir * a * (velocity * 0.75f);
			vel *= 0.85f;
		}
		if (hookedPlayer == player->id && tuningPlayerHooking) {
			glm::vec3 dir = glm::normalize(pos - player->pos);
			if (distance > physSize * 1.50f) {
				float accel = tuningHookDragAccel * (distance / tuningHookLength);
				float dragSpeed = tuningHookDragSpeed;
				{
					player->vel += accel * dir * 1.5f;
					if (glm::length(player->vel) > dragSpeed) {
						player->vel = glm::normalize(player->vel) * dragSpeed;
					}
				}
				{
					vel += -accel * dir * 0.25f;
					if (glm::length(vel) > dragSpeed) {
						vel = glm::normalize(vel) * dragSpeed;
					}
				}
			}
		}
	}
	if (glm::length(vel) > 6000.0f) {
		vel = glm::normalize(vel) * 6000.0f;
	}

	float RampValue = VelocityRamp(glm::length(vel) * 50, tuningVelrampStart,
	                               tuningVelrampRange, tuningVelrampCurvature);
	vel.x = vel.x * RampValue;
	vel.y = vel.y * RampValue;
	glm::vec3 NewPos = pos;
	world->MoveBox(&NewPos, &vel, glm::vec3(physSize, physSize, physSize), 0);
	vel.x = vel.x * (1.0f / RampValue);
	vel.y = vel.y * (1.0f / RampValue);
	if (tuningPlayerColision) {
		glm::vec3 collidePos;
		if (world->IntersectPlayer(pos, NewPos, nullptr, &collidePos, id,
		                           physSize / 2) != nullptr) {
			NewPos = collidePos;
		}
	}
	pos = NewPos;
	if (pos.z < -6000) {
		pos = glm::vec3(100, 100, 6000);
	}
}
