#include "PlayerModel.h"
#include "Sphere.h"
#include "../Graphics.h"
#include "Resources.h"
#include "../../../tools/Player.h"

const int EyeScale = (int)(BaseSize*0.40);
const float Separation=(0.075f*BaseSize)-EyeScale/2;
const int detalization=16;
vec3 PlayerModel::weaponPos[NUM_WEAPONS]={
		vec3(0,1,0),
		vec3(0,1,0),
		vec3(17,3,-5),
		vec3(17,3,-5),
		vec3(0,1,0),
		vec3(0,1,0),
	};
void PlayerModel::render(){
	m_Graphics->PushMatrix();

	m_Graphics->Translate(position);
	m_Graphics->RotateZ(rot);
	Body->render();
	lFoot->render();
	rFoot->render();
	m_Graphics->RotateX(rot);
	m_Graphics->RotateY(rot);

	lArm->render();
	rArm->render();

	m_Graphics->m_Resources->weaponModels[weapon]->position=weaponPos[weapon];
	m_Graphics->m_Resources->weaponModels[weapon]->render();
	
	Eyes->render();
	m_Graphics->PopMatrix();
}
PlayerModel::PlayerModel(Graphics* g):Model(g){
}
void PlayerModel::create(){
	lArm=new Sphere(m_Graphics,true,detalization,detalization,vec3(1,1,1),RenderSize/8,m_Graphics->m_Resources->texturePos8x4[6],false);
	rArm=new Sphere(m_Graphics,true,detalization,detalization,vec3(1,1,1),RenderSize/8,m_Graphics->m_Resources->texturePos8x4[6],true);
	lFoot=new Sphere(m_Graphics,true,detalization,detalization,vec3(0.7f,1,0.5f),RenderSize/2.4f,m_Graphics->m_Resources->texturePos8x4[14]+m_Graphics->m_Resources->texturePos8x4[15],false);
	rFoot=new Sphere(m_Graphics,true,detalization,detalization,vec3(0.7f,1,0.5f),RenderSize/2.4f,m_Graphics->m_Resources->texturePos8x4[14]+m_Graphics->m_Resources->texturePos8x4[15],true);
	Body=new Sphere(m_Graphics,true,detalization,detalization,vec3(1,1,1),RenderSize/2,m_Graphics->m_Resources->texturePos8x4[0]+m_Graphics->m_Resources->texturePos8x4[18],false);
	Eyes=new Model(GL_TRIANGLES,m_Graphics,false);
	
	lArm->create();
	rArm->create();
	lFoot->create();
	rFoot->create();
	Body->create();

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
	Eyes->position=vec3(0,(0.285f*BaseSize),((0.05f)*BaseSize)-EyeScale/2);
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
	lFoot->position=vec3(-RenderSize/2,RenderSize/6,-RenderSize/2);
	rFoot->position=vec3(RenderSize/2,RenderSize/6,-RenderSize/2);

	
	Eyes->clear();
	Eyes->addQuad(quad3(vec3(-EyeScale-Separation,0,EyeScale),vec3(0-Separation,0,EyeScale),vec3(0-Separation,0,0),vec3(-EyeScale-Separation,0,0)),vec3(0,1,0),m_Graphics->m_Resources->texturePos8x4[26+emote].reflectX());
	Eyes->addQuad(quad3(vec3(0+Separation,0,EyeScale),vec3(EyeScale+Separation,0,EyeScale),vec3(EyeScale+Separation,0,0),vec3(Separation,0,0)),vec3(0,1,0),m_Graphics->m_Resources->texturePos8x4[26+emote]);
	Eyes->create();
}