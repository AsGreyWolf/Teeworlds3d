#include "Players.h"
#include <cstdlib>
#include "../Client.h"
#include "Graphics.h"
#include "Camera.h"
#include "graphics/Model2d.h"
#include "graphics/PlayerModel.h"
#include "graphics/Resources.h"

// TODO just for debug
Player* p[128];
PlayerModel* n[128];
Model2d* cursor;
bool Players::OnInit(){
	// TODO just for debug
	for(int i=0;i<128;i++){
		n[i]=new PlayerModel(m_Client->m_Graphics);
		n[i]->create();
		p[i]=new Player();
		p[i]->pos=vec3(rand()%2048,rand()%2048,70);
		p[i]->dir=vec3(rand()/ (static_cast <float> (RAND_MAX/(M_PI*2))),rand()/(static_cast <float> (RAND_MAX/(M_PI*2))),rand()/(static_cast <float> (RAND_MAX/(M_PI*2))));
		p[i]->dir=vec3(0,0,0);
		p[i]->weapon=WEAPON_SHOTGUN;
		p[i]->emote=EMOTE_SURPRISE;
		p[i]->skin="default";
		p[i]->color=vec4(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),static_cast <float> (rand()) / static_cast <float> (RAND_MAX),static_cast <float> (rand()) / static_cast <float> (RAND_MAX),1);
		n[i]->update(p[i]);
	}
	cursor=new Model2d(m_Client->m_Graphics);
	cursor->addQuad(quad2(-0.0625f,-0.0625f,0.125f,0.125f),m_Client->m_Graphics->m_Resources->gameCursor[0]);
	cursor->texture=m_Client->m_Graphics->m_Resources->textureGame;
	cursor->create();
	return true;
}
void Players::OnInput(unsigned char* keys,int xrel,int yrel,int wheel){
	if(wheel>0){
		p[0]->weapon++;
		p[0]->weapon=p[0]->weapon%NUM_WEAPONS;
	}else if(wheel<0){
		p[0]->weapon--;
		if(p[0]->weapon==-1) p[0]->weapon+=NUM_WEAPONS;
	}
	if(keys[SDL_SCANCODE_KP_8]){
		p[0]->dir.x+=0.2f*m_Client->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_2]){
		p[0]->dir.x-=0.2f*m_Client->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_4]){
		p[0]->dir.z+=0.2f*m_Client->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_6]){
		p[0]->dir.z-=0.2f*m_Client->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_7]){
		p[0]->dir.y-=0.2f*m_Client->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_9]){
		p[0]->dir.y+=0.2f*m_Client->tickCoeff;
	}
}
void Players::OnStateChange(STATE lastState){}
void Players::OnQuit(){
	delete cursor;
}
void Players::OnRender(){
	for(int i=0;i<128;i++){
		p[i]->weapon=p[0]->weapon;
		vec3 razn=normalize(m_Client->m_Camera->position-p[i]->pos);
		vec2 xy=normalize(vec2(razn.x,razn.y));
		p[i]->dir=vec3(asin(razn.z),0,xy.x>0.0?-acos(xy.y):acos(xy.y));
		//m_Client->m_Camera->rotation=p[0]->dir;
		n[i]->update(p[i]);
		n[i]->render();
	}
}
void Players::OnRender2d(){
	cursor->render();
}
void Players::OnTick(){}
void Players::OnMessage(int type,char* value){}
