#include "PlayerModel.h"
#include <client/components/Loading.h>
#include <client/components/Resources.h>
#include <client/components/graphics/geometry/Sphere.h>
#include <shared/System.h>

const float PlayerModel::renderSize = 36.0f;
const float PlayerModel::baseSize = 64.0;
const int PlayerModel::eyeScale = static_cast<int>(baseSize * 0.40);
const float PlayerModel::eyeSeparation = (0.075f * baseSize) - eyeScale / 2;
const int PlayerModel::detalization = 32;
const int PlayerModel::animSpeed = 300;
const glm::vec3 PlayerModel::eyesPos =
    glm::vec3(0, (0.285f * baseSize), ((0.05f) * baseSize) - eyeScale / 2);
const glm::vec3 PlayerModel::lFootPos =
    glm::vec3(-renderSize / 2, renderSize / 6,
              -renderSize / 1.5f + renderSize / 4.8f - 5);
const glm::vec3 PlayerModel::rFootPos = glm::vec3(
    renderSize / 2, renderSize / 6, -renderSize / 1.5f + renderSize / 4.8f - 5);

PlayerModel::PlayerModel() : Model3d() {
	g_Loading()->Push([&]() {
		Sphere arm = Sphere()
		                 .SetRadius(renderSize / 8)
		                 .SetTexCoord(g_Resources()->texturePos8x4[6])
		                 .SetRings(detalization)
		                 .SetSectors(detalization);
		lArm.Add(arm);
		rArm.Add(arm.SetReversed(true));
		Sphere foot = Sphere()
		                  .SetRadius(renderSize / 2.4f)
		                  .SetTexCoord(g_Resources()->texturePos8x4[14] >>
		                               g_Resources()->texturePos8x4[15])
		                  .SetRings(detalization)
		                  .SetSectors(detalization)
		                  .SetScale(glm::vec3(0.7f, 1, 0.5f));
		lFoot.Add(foot);
		rFoot.Add(foot.SetReversed(true));
		body.Add(Sphere()
		             .SetRadius(renderSize / 2)
		             .SetTexCoord(g_Resources()->texturePos8x4[0] >>
		                          g_Resources()->texturePos8x4[21])
		             .SetRings(detalization)
		             .SetSectors(detalization));
	});
	lFoot.rot = rot3(0, 0, 5.0f / 180 * M_PI);
	rFoot.rot = rot3(0, 0, -5.0f / 180 * M_PI);
	lArm.rot = rot3(0, 0, -M_PI_2);
	rArm.rot = rot3(0, 0, M_PI_2);
	body.rot = rot3(0, 0, -M_PI_2);
	rFoot.pos = rFootPos;
	lFoot.pos = lFootPos;
	weapon = g_Resources()->weaponModels[0];
	animState = ANIMSTATE_NONE;
	animStart = 0;
	animFase = 0;
}
PlayerModel::PlayerModel(const PlayerModel &second) : Model3d(second) {
	lArm = second.lArm;
	rArm = second.rArm;
	lFoot = second.lFoot;
	rFoot = second.rFoot;
	body = second.body;
	eyes = second.eyes;
	weapon = second.weapon;
	animState = second.animState;
	animStart = second.animStart;
	animFase = second.animFase;
	hook = second.hook;
}
PlayerModel::~PlayerModel() = default;
void PlayerModel::Enable() {
	Model3d::Enable();
	lArm.Enable();
	rArm.Enable();
	lFoot.Enable();
	rFoot.Enable();
	body.Enable();
	eyes.Enable();
	weapon.Enable();
}
void PlayerModel::Disable() {
	Model3d::Disable();
	lArm.Disable();
	rArm.Disable();
	lFoot.Disable();
	rFoot.Disable();
	body.Disable();
	eyes.Disable();
	weapon.Disable();
	for (Model3d &part : hook) {
		part.Disable();
	}
}
void PlayerModel::UpdateMatrix(const glm::mat4 &parentMatrix) {
	modelMatrix = parentMatrix;
	modelMatrix = glm::translate(modelMatrix, pos);
	for (Model3d &part : hook) {
		part.UpdateMatrix(modelMatrix);
	}
	lArm.UpdateMatrix(modelMatrix);
	modelMatrix = glm::rotate(modelMatrix, rot.z, glm::vec3(0, 0, 1));
	lFoot.UpdateMatrix(modelMatrix);
	rFoot.UpdateMatrix(modelMatrix);
	body.UpdateMatrix(modelMatrix);
	modelMatrix = glm::rotate(modelMatrix, rot.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, rot.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, scale);
	// normalMatrix = glm::transpose(glm::inverse(modelMatrix));
	rArm.UpdateMatrix(modelMatrix);
	eyes.UpdateMatrix(modelMatrix);
	weapon.UpdateMatrix(modelMatrix);
}
PlayerModel &PlayerModel::operator=(const PlayerModel &second) {
	lArm = second.lArm;
	rArm = second.rArm;
	lFoot = second.lFoot;
	rFoot = second.rFoot;
	body = second.body;
	eyes = second.eyes;
	weapon = second.weapon;
	hook = second.hook;
	return dynamic_cast<PlayerModel &>(Model3d::operator=(second));
}
void PlayerModel::Sync(const Player &data) {
	pos = data.pos;
	rot = data.rot;
	eyes = g_Resources()->eyesModels[data.emote];
	eyes.pos = eyesPos;
	weapon = g_Resources()->weaponModels[data.weapon];
	weapon.pos = weaponPos[data.weapon];
	rArm.pos = weaponPos[data.weapon];

	Texture &texture = g_Resources()->skinTextures["default"];
	if (g_Resources()->skinTextures.find(data.skin) !=
	    g_Resources()->skinTextures.end()) {
		texture = g_Resources()->skinTextures[data.skin];
	}
	lFoot.texture = texture;
	rFoot.texture = texture;
	lArm.texture = texture;
	rArm.texture = texture;
	eyes.texture = texture;
	body.texture = texture;

	lFoot.color = data.color * ((data.jumped & 2) != 0 ? 0.5f : 1.0f);
	rFoot.color = data.color * ((data.jumped & 2) != 0 ? 0.5f : 1.0f);
	lArm.color = data.color;
	rArm.color = data.color;
	body.color = data.color;
	eyes.color.a = data.color.a;
	weapon.color.a = data.color.a;

	// foot animations
	bool animate = data.grounded && (fabs(data.vel.x) > 1 || fabs(data.vel.y) > 1);
	if (animate) {
		animDir = glm::normalize(glm::vec2(rotate(data.vel, -data.rot)));
	}
	if (animate && animState == ANIMSTATE_NONE) {
		animState++;
		animStart = g_System()->GetTime();
	}
	float dd = g_System()->GetTime() - animStart;
	/// TODO: animSpeed by velocity
	dd /= (animSpeed);
	if (animState == ANIMSTATE_LEFT_ONLY && dd >= 0.5f) {
		animState++;
	}
	dd *= 2 * M_PI;
	float faseA = renderSize / 2 * asin(sin(dd)) / M_PI_2;
	float faseB = renderSize / 6 * cos(dd);
	if (animState == ANIMSTATE_ALL && !animate && faseB > 0 && animFase < 0 &&
	    faseA > 0) {
		animState++;
	}
	if (animState == ANIMSTATE_RIGHT_ONLY && faseB < 0 && animFase > 0 &&
	    faseA < 0) {
		animState = ANIMSTATE_NONE;
	}

	rFoot.pos = rFootPos;
	if (animState == ANIMSTATE_ALL || animState == ANIMSTATE_RIGHT_ONLY) {
		rFoot.pos += glm::vec3(0.5 * faseA * animDir.x, faseA * animDir.y,
		                       glm::max(0.0f, faseB));
	}
	lFoot.pos = lFootPos;
	if (animState == ANIMSTATE_ALL || animState == ANIMSTATE_LEFT_ONLY) {
		lFoot.pos += glm::vec3(-0.5 * faseA * animDir.x, -faseA * animDir.y,
		                       glm::max(0.0f, -faseB));
	}

	animFase = faseA;

	// hook and arm
	if (data.hookState > 0) {
		glm::vec3 hookRelativePos = data.hookPos - data.pos;
		float hookLen = glm::length(hookRelativePos);
		glm::vec3 hookDir = glm::normalize(hookRelativePos);
		rot3 hookRot = rot3(hookDir);
		size_t i = 0;
		if (i == hook.size()) {
			hook.push_back(g_Resources()->hookHead);
		}
		for (float partPos = -10; partPos >= -hookLen; partPos -= 10) {
			hook[i].Enable();
			hook[i].pos = hookRelativePos + hookDir * partPos;
			hook[i].rot = hookRot;
			hook[i].color.a = data.color.a;
			i++;
			if (i == hook.size()) {
				hook.push_back(g_Resources()->hookBody);
			}
		}
		while (i != hook.size()) {
			hook.pop_back();
		}
		lArm.pos = hookDir * renderSize / 2.0f;
	} else {
		hook.clear();
		lArm.pos = glm::vec3(0, 0, 0);
	}
}
