#include "PlayerModel.h"
#include "Text3d.h"
#include "BufferedModel.h"
#include "../Resources.h"
#include "../TextGenerator.h"
#include "../../Graphics.h"
#include "../../../Client.h"
#include "../../../components/Camera.h"
#include "../../../../shared/System.h"
#include "../../../../shared/world/Player.h"

const vec3 PlayerModel::weaponPos[NUM_WEAPONS]={
		vec3(17, 2, 20),
		vec3(17,3,-5),
		vec3(17,3,-5),
		vec3(17,3,-5),
		vec3(17,3,-5),
		vec3(0,1,0),
	};
const float PlayerModel::renderSize = 36.0f;
const float PlayerModel::baseSize = 64.0f;
const int PlayerModel::eyescale = (int)(PlayerModel::baseSize*0.40);
const float PlayerModel::separation = (0.075f*PlayerModel::baseSize) - eyescale / 2;
const int PlayerModel::detalization = 32;
const int PlayerModel::animSpeed = 300;
void PlayerModel::SetMatrix(const glm::mat4& parentMatrix) {
	modelMatrix = parentMatrix;
	nickName->SetMatrix(modelMatrix);
	nickNameShadow->SetMatrix(modelMatrix);
	/*g_Graphics()->m_Resources->hookModels[hookUnits]->position = hookPos;
	g_Graphics()->m_Resources->hookModels[hookUnits]->rotation = hookRot;
	g_Graphics()->m_Resources->hookModels[hookUnits]->modelMatrix = hookModelMatrix;
	g_Graphics()->m_Resources->hookModels[hookUnits]->normalMatrix = hookNormalMatrix;
	g_Graphics()->m_Resources->hookModels[hookUnits]->Render();
	hookModelMatrix = g_Graphics()->m_Resources->hookModels[hookUnits]->modelMatrix;
	hookNormalMatrix = g_Graphics()->m_Resources->hookModels[hookUnits]->normalMatrix;*/
	g_Graphics()->Translate(modelMatrix, position);
	g_Graphics()->RotateZ(modelMatrix, rotation);
	lFoot->SetMatrix(modelMatrix);
	rFoot->SetMatrix(modelMatrix);
	g_Graphics()->RotateX(modelMatrix, rotation);
	body->SetMatrix(modelMatrix);
	g_Graphics()->RotateY(modelMatrix, rotation);
	lArm->SetMatrix(modelMatrix);
	rArm->SetMatrix(modelMatrix);
	weapon->SetMatrix(modelMatrix);
	eyes->SetMatrix(modelMatrix);
}
PlayerModel::PlayerModel():Model(){
	lArm = new Model();
	lArm->AddSphere(vec3(0, 0, 0), detalization, detalization, vec3(1, 1, 1), renderSize / 8, g_Graphics()->m_Resources->texturePos8x4[6], false);
	rArm = new Model();
	rArm->AddSphere(vec3(0, 0, 0), detalization, detalization, vec3(1, 1, 1), renderSize / 8, g_Graphics()->m_Resources->texturePos8x4[6], true);
	lFoot = new Model();
	lFoot->AddSphere(vec3(0, 0, 0), detalization, detalization, vec3(0.7f, 1, 0.5f), renderSize / 2.4f, g_Graphics()->m_Resources->texturePos8x4[14] >> g_Graphics()->m_Resources->texturePos8x4[15], false);
	rFoot = new Model();
	rFoot->AddSphere(vec3(0, 0, 0), detalization, detalization, vec3(0.7f, 1, 0.5f), renderSize / 2.4f, g_Graphics()->m_Resources->texturePos8x4[14] >> g_Graphics()->m_Resources->texturePos8x4[15], true);
	body = new Model();
	body->AddSphere(vec3(0, 0, 0), detalization, detalization, vec3(1, 1, 1), renderSize / 2, g_Graphics()->m_Resources->texturePos8x4[0] >> g_Graphics()->m_Resources->texturePos8x4[21], false);
	eyes = new Model(false);
	nickName = new Text3d("", TextGenerator::FONT_NORMAL, TextGenerator::ALIGN_CENTER_BOTTOM);
	nickNameShadow = new Model(false,true);
	weapon = new BufferedModel(g_Graphics()->m_Resources->weaponModels[0]);

	lFoot->rotation = vec3(0, 0, 5.0f / 180 * M_PI);
	rFoot->rotation = vec3(0, 0, -5.0f / 180 * M_PI);
	lArm->texture = texture;
	lArm->rotation = vec3(0, 0, -M_PI_2);
	rArm->texture = texture;
	rArm->rotation = vec3(0, 0, M_PI_2);
	lFoot->texture = texture;
	rFoot->texture = texture;
	body->texture = texture;
	body->rotation = vec3(0, 0, -M_PI_2);
	eyes->texture = texture;
	rFoot->position = vec3(renderSize / 2, renderSize / 6, -renderSize / 1.5f + renderSize / 4.8f - 5);
	lFoot->position = vec3(-renderSize / 2, renderSize / 6, -renderSize / 1.5f + renderSize / 4.8f - 5);
	eyes->position = vec3(0, (0.285f*baseSize), ((0.05f)*baseSize) - eyescale / 2);
	nickNameShadow->color = vec4(0, 0, 0, 0.5f);

	animState = ANIMSTATE_NONE;
}
void PlayerModel::Create(){
	lArm->Create();
	rArm->Create();
	lFoot->Create();
	rFoot->Create();
	body->Create();
	eyes->Create();
	nickName->Create();
	nickNameShadow->Create();
	weapon->Create();
}
PlayerModel::~PlayerModel(){
	delete lArm;
	delete rArm;
	delete lFoot;
	delete rFoot;
	delete body;
	delete eyes;
	delete nickName;
	delete nickNameShadow;
	delete weapon;
}
void PlayerModel::Update(Player* p){
	position = p->pos;
	rotation = p->rot;
	hookPos = p->hookPos;
	hookRot = quad2::vec2rot(p->hookPos - p->pos);
	hookUnits = glm::max(glm::min(length(p->hookPos - p->pos)/12, 32.0f),1.0f)-1;
	weapon->model=g_Graphics()->m_Resources->weaponModels[p->weapon];
	weapon->position = weaponPos[p->weapon];
	emote=p->emote;
	if (g_Graphics()->m_Resources->skinTextures.find(p->skin) != g_Graphics()->m_Resources->skinTextures.end())
		texture = g_Graphics()->m_Resources->skinTextures[p->skin];
	else
		texture = g_Graphics()->m_Resources->skinTextures["default"];
	lFoot->texture=texture;
	rFoot->texture=texture;
	lArm->texture=texture;
	rArm->texture=texture;
	eyes->texture=texture;
	body->texture=texture;

	lFoot->color=p->color*(p->jumped & 2 ? 0.5f : 1.0f);
	rFoot->color=p->color*(p->jumped & 2 ? 0.5f : 1.0f);
	lArm->color=p->color;
	rArm->color=p->color;
	body->color=p->color;


	rArm->position=weaponPos[p->weapon];

	bool anim=p->grounded && (abs(p->vel.x) > 1 || abs(p->vel.y) > 1);
	if(anim && animState==ANIMSTATE_NONE){
		animState++;
		animStart=g_System()->GetTime();
	}
	float dd = g_System()->GetTime() - animStart;
	///TODO: animSpeed from velocity
	dd/=(animSpeed);
	if(animState==ANIMSTATE_LEFT_ONLY && dd>=0.5f)
		animState++;
	dd*=2*M_PI;
	float faseA=renderSize/2*sin(dd);
	float faseB=renderSize/6*cos(dd);
	if(animState==ANIMSTATE_ALL && !anim && faseB>0 && lastFaseA<0 && faseA>0)
		animState++;
	if(animState==ANIMSTATE_RIGHT_ONLY && faseB<0 && lastFaseA>0 && faseA<0)
		animState=ANIMSTATE_NONE;
	if(animState==ANIMSTATE_ALL || animState==ANIMSTATE_RIGHT_ONLY)
		rFoot->position = vec3(renderSize / 2, renderSize / 6 + faseA, -renderSize / 1.5f + renderSize / 4.8f + glm::max(0.0f, faseB) - 5);
	else
		rFoot->position = vec3(renderSize / 2, renderSize / 6, -renderSize / 1.5f + renderSize / 4.8f - 5);
	if(animState==ANIMSTATE_ALL || animState==ANIMSTATE_LEFT_ONLY)
		lFoot->position = vec3(-renderSize / 2, renderSize / 6 - faseA, -renderSize / 1.5f + renderSize / 4.8f + glm::max(0.0f, -faseB) - 5);
	else
		lFoot->position = vec3(-renderSize / 2, renderSize / 6, -renderSize / 1.5f + renderSize / 4.8f - 5);
	lastFaseA=faseA;

	
	eyes->Clear();
	eyes->AddQuad(quad3(vec3(-eyescale - separation, 0, eyescale), vec3(0 - separation, 0, eyescale), vec3(0 - separation, 0, 0), vec3(-eyescale - separation, 0, 0)), vec3(0, 1, 0), g_Graphics()->m_Resources->texturePos8x4[26 + emote].reflectX());
	eyes->AddQuad(quad3(vec3(0 + separation, 0, eyescale), vec3(eyescale + separation, 0, eyescale), vec3(eyescale + separation, 0, 0), vec3(separation, 0, 0)), vec3(0, 1, 0), g_Graphics()->m_Resources->texturePos8x4[26 + emote]);
	eyes->Create();
	if(nickName->text!=p->nickname){
		delete nickName;
		nickName = new Text3d(p->nickname, TextGenerator::FONT_NORMAL, TextGenerator::ALIGN_CENTER_BOTTOM);
		nickName->Create();

		nickNameShadow->Clear();
		quad2 geom=nickName->data->geometry*100;
		nickNameShadow->AddRectangle(geom,quad2(geom.p00+vec2(-1,-1),geom.p10+vec2(1,-1),geom.p01+vec2(-1,1),geom.p11+vec2(1,1)),-1);
		nickNameShadow->Create();
	}
	nickName->position=p->pos;
	nickNameShadow->position=p->pos;
	nickName->position.z+=renderSize/2+2;
	nickNameShadow->position.z+=renderSize/2+2;
}