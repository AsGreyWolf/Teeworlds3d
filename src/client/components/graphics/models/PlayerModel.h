#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include "Model3d.h"
#include <vector>
#define GLEW_STATIC
#include <glew.h>
#include <tools/vmath.h>
#include <shared/world/Player.h>
#include <client/components/graphics/Texture.h>

class PlayerModel : public Model3d {
public:
	PlayerModel();
	PlayerModel(const PlayerModel &second);
	~PlayerModel() override;
	void Enable() override;
	void Disable() override;
	void UpdateMatrix(const glm::mat4 &parentMatrix = glm::mat4(1.0f)) override;

	PlayerModel &operator=(const PlayerModel &second);

	void Sync(const Player &data);

	const glm::vec3 weaponPos[NUM_WEAPONS] = {
	    glm::vec3(17, 2, 20), glm::vec3(17, 3, -5), glm::vec3(17, 3, -5),
	    glm::vec3(17, 3, -5), glm::vec3(17, 3, -5), glm::vec3(0, 1, 0),
	};
	static const float renderSize;
	static const float baseSize;
	static const int eyeScale;
	static const float eyeSeparation;

protected:
	Model3d lArm;
	Model3d rArm;
	Model3d lFoot;
	Model3d rFoot;
	Model3d body;
	Model3d eyes;
	Model3d weapon;
	std::vector<Model3d> hook;

	enum ANIMSTATES {
		ANIMSTATE_NONE = 0,
		ANIMSTATE_LEFT_ONLY,
		ANIMSTATE_ALL,
		ANIMSTATE_RIGHT_ONLY,
	};
	int animState;
	float animStart;
	float animFase;
	glm::vec2 animDir;

	static const int detalization;
	static const int animSpeed;
	static const glm::vec3 eyesPos;
	static const glm::vec3 lFootPos;
	static const glm::vec3 rFootPos;
};

#endif
