#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include "Model.h"
#include "../../../tools/Protocol.h"
class Player;

///<summary>Visual player object</summary>
class PlayerModel : public Model
{
public:
	PlayerModel();
	///<summary>Initializes subModels and creates them</summary>
	void Create();
	///<summary>Pushes the subModels into the shader</summary>
	void Render(const glm::mat4 &parentMatrix);
	void Render(){
		Render(glm::mat4(1.0f));
	}
	///<summary>Pushes the billboards into the shader</summary>
	void RenderBillboard();
	///<summary>Removes the subModels</summary>
	void Remove();
	///<summary>Updates model with player info</summary>
	///<param name="p">Player info</param>
	void Update(Player* p);

	const float renderSize = 36.0f;
	const float baseSize = 64.0f;
private:
	Model* lArm;
	Model* rArm;
	Model* lFoot;
	Model* rFoot;
	Model* body;
	Model* eyes;
	Model* nickName;
	Model* nickNameShadow;
	bool visible;
	int weapon;
	int emote;


	void addQuad(){};
	void addVertex(std::vector<vec3> v,std::vector<vec3> n,std::vector<vec2> t,vec3 c){};
	void addVertex(vec3 v,vec3 n,vec2 t,vec3 c){};
	void clear(){};

	float animStart;
	enum{
		ANIMSTATE_NONE=0,
		ANIMSTATE_LEFT_ONLY,
		ANIMSTATE_ALL,
		ANIMSTATE_RIGHT_ONLY,
	};
	int animState;
	float lastFaseA;

	static vec3 weaponPos[NUM_WEAPONS];
	glm::mat4 gunModelMatrix;
	glm::mat4 gunNormalMatrix;

	const int eyescale = (int)(baseSize*0.40);
	const float separation = (0.075f*baseSize) - eyescale / 2;
	const int detalization = 32;
	const int animSpeed = 300;
};

#endif
