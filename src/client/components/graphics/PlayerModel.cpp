#include "PlayerModel.h"
#include "../Graphics.h"
#include "Resources.h"
#include "../../../tools/Player.h"
#include "../../../tools/system.h"
#include "Text3d.h"
#include "TextGenerator.h"
#include "../../Client.h"
#include "../../components/Camera.h"

const int eyescale = (int)(baseSize*0.40);
const float separation=(0.075f*baseSize)-eyescale/2;
const int detalization=32;
const int animSpeed=300;
vec3 PlayerModel::weaponPos[NUM_WEAPONS]={
		vec3(17, 2, 20),
		vec3(17,3,-5),
		vec3(17,3,-5),
		vec3(17,3,-5),
		vec3(17,3,-5),
		vec3(0,1,0),
	};
void PlayerModel::RenderBillboard(){
	nickName->LookAt(g_Camera()->position);
	nickNameShadow->LookAt(g_Camera()->position);
	nickName->ScaleAt(g_Camera()->position, vec3(0), vec3(0.002f));
	nickNameShadow->ScaleAt(g_Camera()->position, vec3(0), vec3(0.002f));
	nickName->scale+=1;
	nickNameShadow->scale+=1;
	nickNameShadow->Render();
	nickName->Render();
}
void PlayerModel::Render(const glm::mat4 &parentMatrix){
	if (!g_Graphics()->restoreMatrix)
		modelMatrix=parentMatrix;

	g_Graphics()->Translate(modelMatrix, position);
	g_Graphics()->RotateZ(modelMatrix, rot);
	lFoot->Render(modelMatrix);
	rFoot->Render(modelMatrix);
	g_Graphics()->RotateX(modelMatrix, rot);
	body->Render(modelMatrix);
	g_Graphics()->RotateY(modelMatrix, rot);

	lArm->Render(modelMatrix);
	rArm->Render(modelMatrix);

	g_Graphics()->m_Resources->weaponModels[weapon]->position = weaponPos[weapon];
	g_Graphics()->m_Resources->weaponModels[weapon]->modelMatrix = gunModelMatrix;
	g_Graphics()->m_Resources->weaponModels[weapon]->normalMatrix = gunNormalMatrix;
	g_Graphics()->m_Resources->weaponModels[weapon]->Render(modelMatrix);
	gunModelMatrix = g_Graphics()->m_Resources->weaponModels[weapon]->modelMatrix;
	gunNormalMatrix = g_Graphics()->m_Resources->weaponModels[weapon]->normalMatrix;
	
	eyes->Render(modelMatrix);
}
PlayerModel::PlayerModel():Model(){
}
void PlayerModel::Create(){
	lArm=new Model();
	lArm->AddSphere(detalization, detalization, vec3(1, 1, 1), renderSize / 8, g_Graphics()->m_Resources->texturePos8x4[6], false);
	rArm=new Model();
	rArm->AddSphere(detalization, detalization, vec3(1, 1, 1), renderSize / 8, g_Graphics()->m_Resources->texturePos8x4[6], true);
	lFoot=new Model();
	lFoot->AddSphere(detalization, detalization, vec3(0.7f, 1, 0.5f), renderSize / 2.4f, g_Graphics()->m_Resources->texturePos8x4[14] >> g_Graphics()->m_Resources->texturePos8x4[15], false);
	rFoot=new Model();
	rFoot->AddSphere(detalization, detalization, vec3(0.7f, 1, 0.5f), renderSize / 2.4f, g_Graphics()->m_Resources->texturePos8x4[14] >> g_Graphics()->m_Resources->texturePos8x4[15], true);
	body=new Model();
	body->AddSphere(detalization, detalization, vec3(1, 1, 1), renderSize / 2, g_Graphics()->m_Resources->texturePos8x4[0] >> g_Graphics()->m_Resources->texturePos8x4[21], false);
	eyes=new Model(false);
	nickName=new Text3d();
	nickNameShadow=new Model(false);
	
	lArm->Create();
	rArm->Create();
	lFoot->Create();
	rFoot->Create();
	body->Create();
	eyes->Create();
	nickName->Create();
	nickNameShadow->Create();

	lFoot->rot=vec3(0,0,5.0f/180*M_PI);
	rFoot->rot=vec3(0,0,-5.0f/180*M_PI);
	lArm->texture=texture;
	lArm->rot=vec3(0,0,-M_PI_2);
	rArm->texture=texture;
	rArm->rot=vec3(0,0,M_PI_2);
	lFoot->texture=texture;
	rFoot->texture=texture;
	body->texture=texture;
	body->rot=vec3(0,0,-M_PI_2);
	eyes->texture=texture;
	rFoot->position=vec3(renderSize/2,renderSize/6,-renderSize/2);
	lFoot->position=vec3(-renderSize/2,renderSize/6,-renderSize/2);
	eyes->position=vec3(0,(0.285f*baseSize),((0.05f)*baseSize)-eyescale/2);
	nickNameShadow->coloring=vec4(0,0,0,0.5f);

	animState=ANIMSTATE_NONE;
}
void PlayerModel::Remove(){
	delete lArm;
	delete rArm;
	delete lFoot;
	delete rFoot;
	delete body;
	delete eyes;
}
void PlayerModel::Update(Player* p){
	position=p->pos;
	rot = quad2::vec2rot(p->dir);
	weapon=p->weapon;
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

	lFoot->coloring=p->color;
	rFoot->coloring=p->color;
	lArm->coloring=p->color;
	rArm->coloring=p->color;
	body->coloring=p->color;


	rArm->position=weaponPos[p->weapon];

	bool anim=abs(p->vel.x)>=1 || abs(p->vel.y)>=1;
	if(anim && animState==ANIMSTATE_NONE){
		animState++;
		animStart=System::GetTime();
	}
	float dd=System::GetTime()-animStart;
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
		rFoot->position=vec3(renderSize/2,renderSize/6+faseA,-renderSize/2+glm::max(0.0f,faseB));
	else
		rFoot->position=vec3(renderSize/2,renderSize/6,-renderSize/2);
	if(animState==ANIMSTATE_ALL || animState==ANIMSTATE_LEFT_ONLY)
		lFoot->position=vec3(-renderSize/2,renderSize/6-faseA,-renderSize/2+glm::max(0.0f,-faseB));
	else
		lFoot->position=vec3(-renderSize/2,renderSize/6,-renderSize/2);
	lastFaseA=faseA;

	
	eyes->Clear();
	eyes->AddQuad(quad3(vec3(-eyescale - separation, 0, eyescale), vec3(0 - separation, 0, eyescale), vec3(0 - separation, 0, 0), vec3(-eyescale - separation, 0, 0)), vec3(0, 1, 0), g_Graphics()->m_Resources->texturePos8x4[26 + emote].reflectX());
	eyes->AddQuad(quad3(vec3(0 + separation, 0, eyescale), vec3(eyescale + separation, 0, eyescale), vec3(eyescale + separation, 0, 0), vec3(separation, 0, 0)), vec3(0, 1, 0), g_Graphics()->m_Resources->texturePos8x4[26 + emote]);
	eyes->Create();
	if(((Text3d*)nickName)->text!=p->nickname){
		nickName->Clear();
		nickNameShadow->Clear();

		((Text3d*)nickName)->AddText(p->nickname,Resources::FONT_NORMAL,TextGenerator::ALIGN_CENTER_BOTTOM,false);
		quad2 geom=((Text3d*)nickName)->data->geometry*100;
		nickNameShadow->AddRectangle(geom,quad2(geom.p00+vec2(-1,-1),geom.p10+vec2(1,-1),geom.p01+vec2(-1,1),geom.p11+vec2(1,1)),-1);
		nickName->Create();
		nickNameShadow->Create();
	}
	nickName->position=p->pos;
	nickNameShadow->position=p->pos;
	nickName->position.z+=renderSize/2+2;
	nickNameShadow->position.z+=renderSize/2+2;
}