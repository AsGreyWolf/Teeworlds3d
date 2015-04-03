#include "Players.h"
#include <cstdlib>
#include "../Client.h"
#include "Graphics.h"
#include "Camera.h"
#include "graphics/Model2d.h"
#include "graphics/PlayerModel.h"
#include "graphics/Resources.h"

// TODO just for debug
PlayerModel* n[MAX_PLAYERS];
Model2d* cursor;
Players::Players() : Component(){
	Component::mp_Players = this;
	// TODO just for debug
	for(int i=0;i<MAX_PLAYERS;i++){
		n[i]=new PlayerModel();
		n[i]->create();
		players[i]=new Player();
		players[i]->pos=vec3(rand()%2048,rand()%2048,70);
		players[i]->dir=vec3(rand()/ (static_cast <float> (RAND_MAX/(M_PI*2))),rand()/(static_cast <float> (RAND_MAX/(M_PI*2))),rand()/(static_cast <float> (RAND_MAX/(M_PI*2))));
		players[i]->dir=vec3(0,0,0);
		players[i]->weapon=rand()%NUM_WEAPONS;
		players[i]->emote=EMOTE_SURPRISE;
		players[i]->skin="default";
		players[i]->color=vec4(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),static_cast <float> (rand()) / static_cast <float> (RAND_MAX),static_cast <float> (rand()) / static_cast <float> (RAND_MAX),1);
		players[i]->NickName="Happy New Year!";
		n[i]->update(players[i]);
	}
	cursor=new Model2d();
	cursor->addQuad(quad2(-0.0625f, -0.0625f, 0.125f, 0.125f), m_Graphics()->m_Resources->gameCursor[0]);
	cursor->texture = m_Graphics()->m_Resources->textureGame;
	cursor->create();
}
Players::~Players(){
	for(int i=0;i<MAX_PLAYERS;i++){
		delete n[i];
		delete players[i];
	}
	delete cursor;
	Component::mp_Players = NULL;
}
///TODO: debug only
bool lastSpaceState=false;
void Players::Input(unsigned char* keys,int xrel,int yrel,int wheel){
	if(wheel>0){
		for(int i=0;i<MAX_PLAYERS;i++){
			players[i]->weapon++;
			players[i]->weapon=players[i]->weapon%NUM_WEAPONS;
		}
	}else if(wheel<0){
		for(int i=0;i<MAX_PLAYERS;i++){
			players[i]->weapon--;
			if(players[i]->weapon==-1) players[i]->weapon+=NUM_WEAPONS;
		}
	}
	if(keys[SDL_SCANCODE_KP_8]){
		players[0]->dir.x += 0.2f*m_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_2]){
		players[0]->dir.x -= 0.2f*m_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_4]){
		players[0]->dir.z += 0.2f*m_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_6]){
		players[0]->dir.z -= 0.2f*m_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_7]){
		players[0]->dir.y -= 0.2f*m_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_9]){
		players[0]->dir.y += 0.2f*m_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_SPACE]){
		if(!lastSpaceState){
			for(int i=0;i<MAX_PLAYERS;i++)
				players[i]->vel.y=players[i]->vel.y>0?0:1;
			lastSpaceState=true;
		}
	}else{
		lastSpaceState=false;
	}
}
void Players::StateChange(STATE lastState){}
void Players::Render(){
	for(int i=0;i<MAX_PLAYERS;i++){
		n[i]->update(players[i]);
		n[i]->lookAt(m_Camera()->position);
		n[i]->render();
	}
}
void Players::Render2d(){
	cursor->render();
}
void Players::RenderBillboard(){
	for(int i=0;i<MAX_PLAYERS;i++){
		n[i]->renderBillboard();
	}
}
void Players::Tick(){}
void Players::Message(int type,char* value){}
