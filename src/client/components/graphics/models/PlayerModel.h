#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include "Model.h"
#include "../../../../tools/Protocol.h"

class Player;
class Text3d;
class BufferedModel;

///<summary>Visual player object</summary>
class PlayerModel : public Model
{
public:
	PlayerModel();
	///<summary>Initializes subModels and creates them</summary>
	void Create();
	~PlayerModel();
	///<summary>Update matrix</summary>
	void SetMatrix(const glm::mat4& parent = mat4(1.0f));

	///<summary>Updates model with player info</summary>
	///<param name="p">Player info</param>
	void Update(Player* p);
private:
	///Submodels
	Model* lArm;
	Model* rArm;
	Model* lFoot;
	Model* rFoot;
	Model* body;
	Model* eyes;
	Text3d* nickName;
	Model* nickNameShadow;
	BufferedModel* weapon;
	int emote;
	int hookUnits;
	glm::vec3 hookPos;
	glm::vec3 hookRot;

	///<summary>Foot animation state list</summary>
	enum ANIMSTATES{
		ANIMSTATE_NONE=0,
		ANIMSTATE_LEFT_ONLY,
		ANIMSTATE_ALL,
		ANIMSTATE_RIGHT_ONLY,
	};
	///<summary>Foot animation state</summary>
	int animState;
	///<summary>Foot animation start time</summary>
	float animStart;
	float lastFaseA;

	static const vec3 weaponPos[NUM_WEAPONS];
	static const float renderSize;
	static const float baseSize;
	static const int eyescale;
	static const float separation;
	static const int detalization;
	static const int animSpeed;
};

#endif
