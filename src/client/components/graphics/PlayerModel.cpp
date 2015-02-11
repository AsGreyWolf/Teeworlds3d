#include "PlayerModel.h"
#include "../Graphics.h"
#include "Resources.h"
#include "../../../tools/Player.h"
#include "../../../tools/system.h"
#include "Text3d.h"
#include "TextGenerator.h"
#include "../../Client.h"
#include "../../components/Camera.h"

const int EyeScale = (int)(BaseSize*0.40);
const float Separation=(0.075f*BaseSize)-EyeScale/2;
const int detalization=16;
const int animSpeed=300;
vec3 PlayerModel::weaponPos[NUM_WEAPONS]={
		vec3(0,1,0),
		vec3(17,3,-5),
		vec3(17,3,-5),
		vec3(17,3,-5),
		vec3(17,3,-5),
		vec3(0,1,0),
	};
void PlayerModel::renderBillboard(){
	NickName->lookAt(m_Graphics->m_Client->m_Camera->position);
	NickNameShadow->lookAt(m_Graphics->m_Client->m_Camera->position);
	NickName->scaleAt(m_Graphics->m_Client->m_Camera->position,vec3(0),vec3(0.002f));
	NickNameShadow->scaleAt(m_Graphics->m_Client->m_Camera->position,vec3(0),vec3(0.002f));
	NickName->scale+=1;
	NickNameShadow->scale+=1;
	NickName->render();
	NickNameShadow->render();
}
<<<<<<< HEAD
void PlayerModel::render(const glm::mat4 &lastMatrix,bool buffered){
	modelBuffer=lastMatrix;
	if(!buffered){
		m_Graphics->Translate(modelBuffer,position);
		m_Graphics->RotateZ(modelBuffer,rot);
	}
	Body->render(modelBuffer,buffered);
	lFoot->render(modelBuffer,buffered);
	rFoot->render(modelBuffer,buffered);
	if(!buffered){
		m_Graphics->RotateX(modelBuffer,rot);
		m_Graphics->RotateY(modelBuffer,rot);
	}
=======
void PlayerModel::render(){
	m_Graphics->PushMatrix();

	m_Graphics->modelMatrix*=m_Graphics->Translate(position);
	m_Graphics->modelMatrix*=m_Graphics->RotateZ(rot);
	Body->render();
	lFoot->render();
	rFoot->render();
	m_Graphics->modelMatrix*=m_Graphics->RotateX(rot);
	m_Graphics->modelMatrix*=m_Graphics->RotateY(rot);
>>>>>>> parent of f137aad... Fixes

	lArm->render(modelBuffer,buffered);
	rArm->render(modelBuffer,buffered);

	if(!buffered){
		m_Graphics->m_Resources->weaponModels[weapon]->position=weaponPos[weapon];
		m_Graphics->m_Resources->weaponModels[weapon]->render(modelBuffer,buffered);
		weaponModelMatrix=m_Graphics->m_Resources->weaponModels[weapon]->modelBuffer;
		weaponNormalMatrix=m_Graphics->m_Resources->weaponModels[weapon]->normalBuffer;
	}else{
		m_Graphics->m_Resources->weaponModels[weapon]->modelBuffer=weaponModelMatrix;
		m_Graphics->m_Resources->weaponModels[weapon]->normalBuffer=weaponNormalMatrix;
		m_Graphics->m_Resources->weaponModels[weapon]->render(modelBuffer,buffered);
	}
	
	Eyes->render(modelBuffer,buffered);
}
PlayerModel::PlayerModel(Graphics* g):Model(g){
}
void PlayerModel::create(){
	lArm=new Model(m_Graphics);
	lArm->addSphere(detalization,detalization,vec3(1,1,1),RenderSize/8,m_Graphics->m_Resources->texturePos8x4[6],false);
	rArm=new Model(m_Graphics);
	rArm->addSphere(detalization,detalization,vec3(1,1,1),RenderSize/8,m_Graphics->m_Resources->texturePos8x4[6],true);
	lFoot=new Model(m_Graphics);
	lFoot->addSphere(detalization,detalization,vec3(0.7f,1,0.5f),RenderSize/2.4f,m_Graphics->m_Resources->texturePos8x4[14]+m_Graphics->m_Resources->texturePos8x4[15],false);
	rFoot=new Model(m_Graphics);
	rFoot->addSphere(detalization,detalization,vec3(0.7f,1,0.5f),RenderSize/2.4f,m_Graphics->m_Resources->texturePos8x4[14]+m_Graphics->m_Resources->texturePos8x4[15],true);
	Body=new Model(m_Graphics);
	Body->addSphere(detalization,detalization,vec3(1,1,1),RenderSize/2,m_Graphics->m_Resources->texturePos8x4[0]+m_Graphics->m_Resources->texturePos8x4[18],false);
	Eyes=new Model(m_Graphics,false);
	NickName=new Text3d(m_Graphics);
	NickNameShadow=new Model(m_Graphics,false);
	
	lArm->create();
	rArm->create();
	lFoot->create();
	rFoot->create();
	Body->create();
	Eyes->create();
	NickName->create();
	NickNameShadow->create();

	lFoot->rot=vec3(0,0,5.0f/180*M_PI);
	rFoot->rot=vec3(0,0,-5.0f/180*M_PI);
	lArm->texture=texture;
	lArm->rot=vec3(0,0,-M_PI_2);
	rArm->texture=texture;
	rArm->rot=vec3(0,0,M_PI_2);
	lFoot->texture=texture;
	rFoot->texture=texture;
	Body->texture=texture;
	Body->rot=vec3(0,0,-M_PI_2);
	Eyes->texture=texture;
	rFoot->position=vec3(RenderSize/2,RenderSize/6,-RenderSize/2);
	lFoot->position=vec3(-RenderSize/2,RenderSize/6,-RenderSize/2);
	Eyes->position=vec3(0,(0.285f*BaseSize),((0.05f)*BaseSize)-EyeScale/2);
	NickNameShadow->coloring=vec4(0,0,0,0.5f);

	animState=ANIMSTATE_NONE;
}
void PlayerModel::remove(){
	delete lArm;
	delete rArm;
	delete lFoot;
	delete rFoot;
	delete Body;
	delete Eyes;
}
void PlayerModel::update(Player* p){
	position=p->pos;
	rot=p->dir;
	weapon=p->weapon;
	emote=p->emote;
	if(m_Graphics->m_Resources->skinTextures.find(p->skin)!=m_Graphics->m_Resources->skinTextures.end())
		texture=m_Graphics->m_Resources->skinTextures[p->skin];
	else
		texture=m_Graphics->m_Resources->skinTextures["default"];
	lFoot->texture=texture;
	rFoot->texture=texture;
	lArm->texture=texture;
	rArm->texture=texture;
	Eyes->texture=texture;
	Body->texture=texture;

	lFoot->coloring=p->color;
	rFoot->coloring=p->color;
	lArm->coloring=p->color;
	rArm->coloring=p->color;
	Body->coloring=p->color;


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
	float faseA=RenderSize/2*sin(dd);
	float faseB=RenderSize/6*cos(dd);
	if(animState==ANIMSTATE_ALL && !anim && faseB>0 && lastFaseA<0 && faseA>0)
		animState++;
	if(animState==ANIMSTATE_RIGHT_ONLY && faseB<0 && lastFaseA>0 && faseA<0)
		animState=ANIMSTATE_NONE;
	if(animState==ANIMSTATE_ALL || animState==ANIMSTATE_RIGHT_ONLY)
		rFoot->position=vec3(RenderSize/2,RenderSize/6+faseA,-RenderSize/2+glm::max(0.0f,faseB));
	else
		rFoot->position=vec3(RenderSize/2,RenderSize/6,-RenderSize/2);
	if(animState==ANIMSTATE_ALL || animState==ANIMSTATE_LEFT_ONLY)
		lFoot->position=vec3(-RenderSize/2,RenderSize/6-faseA,-RenderSize/2+glm::max(0.0f,-faseB));
	else
		lFoot->position=vec3(-RenderSize/2,RenderSize/6,-RenderSize/2);
	lastFaseA=faseA;

	
	Eyes->clear();
	Eyes->addQuad(quad3(vec3(-EyeScale-Separation,0,EyeScale),vec3(0-Separation,0,EyeScale),vec3(0-Separation,0,0),vec3(-EyeScale-Separation,0,0)),vec3(0,1,0),m_Graphics->m_Resources->texturePos8x4[26+emote].reflectX());
	Eyes->addQuad(quad3(vec3(0+Separation,0,EyeScale),vec3(EyeScale+Separation,0,EyeScale),vec3(EyeScale+Separation,0,0),vec3(Separation,0,0)),vec3(0,1,0),m_Graphics->m_Resources->texturePos8x4[26+emote]);
	Eyes->create();
	if(((Text3d*)NickName)->text!=p->NickName){
		NickName->clear();
		NickNameShadow->clear();

		((Text3d*)NickName)->addText(p->NickName,Resources::FONT_NORMAL,TextGenerator::ALIGN_CENTER_BOTTOM,false);
		quad2 geom=((Text3d*)NickName)->data->geometry*100;
		NickNameShadow->addRectangle(geom,quad2(geom.p00+vec2(-1,-1),geom.p10+vec2(1,-1),geom.p01+vec2(-1,1),geom.p11+vec2(1,1)));
		NickName->create();
		NickNameShadow->create();
	}
	NickName->position=p->pos;
	NickNameShadow->position=p->pos;
	NickName->position.z+=RenderSize/2+2;
	NickNameShadow->position.z+=RenderSize/2+2;
}