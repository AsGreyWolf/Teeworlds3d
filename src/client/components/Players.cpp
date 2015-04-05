#include "Players.h"
#include <cstdlib>
#include "../Client.h"
#include "Graphics.h"
#include "Camera.h"
#include "graphics/Model2d.h"
#include "graphics/PlayerModel.h"
#include "graphics/Resources.h"
#include "../../shared/World.h"
#include "../../tools/Player.h"

class Players* mp_Players;
Players* m_Players(){ return mp_Players; }

// TODO just for debug
Model2d* cursor;
Players::Players() : Component(){
	mp_Players = this;
	// TODO just for debug
	for (int i = 0; i < MAX_PLAYERS; i++){
		playerModels[i] = new PlayerModel();
		playerModels[i]->create();
	}
	cursor=new Model2d();
	cursor->addQuad(quad2(-0.0625f, -0.0625f, 0.125f, 0.125f), m_Graphics()->m_Resources->gameCursor[0]);
	cursor->texture = m_Graphics()->m_Resources->textureGame;
	cursor->create();
}
Players::~Players(){
	for(int i=0;i<MAX_PLAYERS;i++){
		delete playerModels[i];
	}
	delete cursor;
	mp_Players = NULL;
}
///TODO: debug only
bool lastSpaceState=false;
void Players::Input(unsigned char* keys,int xrel,int yrel,int wheel){
	if(wheel>0){
		for(int i=0;i<MAX_PLAYERS;i++){
			m_World()->players[i]->weapon++;
			m_World()->players[i]->weapon = m_World()->players[i]->weapon%NUM_WEAPONS;
		}
	}else if(wheel<0){
		for(int i=0;i<MAX_PLAYERS;i++){
			m_World()->players[i]->weapon--;
			if(m_World()->players[i]->weapon==-1) m_World()->players[i]->weapon+=NUM_WEAPONS;
		}
	}
	if(keys[SDL_SCANCODE_KP_8]){
		m_World()->players[0]->dir.x += 0.2f*m_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_2]){
		m_World()->players[0]->dir.x -= 0.2f*m_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_4]){
		m_World()->players[0]->dir.z += 0.2f*m_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_6]){
		m_World()->players[0]->dir.z -= 0.2f*m_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_7]){
		m_World()->players[0]->dir.y -= 0.2f*m_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_9]){
		m_World()->players[0]->dir.y += 0.2f*m_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_SPACE]){
		if(!lastSpaceState){
			for(int i=0;i<MAX_PLAYERS;i++)
				m_World()->players[i]->vel.y=m_World()->players[i]->vel.y>0?0:1;
			lastSpaceState=true;
		}
	}else{
		lastSpaceState=false;
	}
}
void Players::StateChange(STATE lastState){}
void Players::Render(){
	for(int i=0;i<MAX_PLAYERS;i++){
		playerModels[i]->update(m_World()->players[i]);
		playerModels[i]->render();
	}
}
void Players::Render2d(){
	cursor->render();
}
void Players::RenderBillboard(){
	for(int i=0;i<MAX_PLAYERS;i++){
		playerModels[i]->renderBillboard();
	}
}
void Players::Tick(){}
void Players::Message(int type,char* value){}
