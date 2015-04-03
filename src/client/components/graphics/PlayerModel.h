#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include "Model.h"
#include "../../../tools/Protocol.h"

const float RenderSize = 36.0f;
const float BaseSize = 64.0f;
class Player;

///<summary>Visual player object</summary>
class PlayerModel : public Model
{
public:
	PlayerModel();
	///<summary>Initializes subModels and creates them</summary>
	void create();
	///<summary>Pushes the subModels into the shader</summary>
	void render(const glm::mat4 &parentMatrix);
	void render(){
		render(glm::mat4(1.0f));
	}
	///<summary>Pushes the billboards into the shader</summary>
	void renderBillboard();
	///<summary>Removes the subModels</summary>
	void remove();
	///<summary>Updates model with player info</summary>
	///<param name="p">Player info</param>
	void update(Player* p);
private:
	Model* lArm;
	Model* rArm;
	Model* lFoot;
	Model* rFoot;
	Model* Body;
	Model* Eyes;
	Model* NickName;
	Model* NickNameShadow;
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
};

#endif
