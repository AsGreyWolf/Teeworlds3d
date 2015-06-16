#include "Players.h"
#include <cstdlib>
#include "../Client.h"
#include "Graphics.h"
#include "Camera.h"
#include "graphics/Model2d.h"
#include "graphics/PlayerModel.h"
#include "graphics/Resources.h"
#include "../../shared/World.h"
#include "../../shared/world/Player.h"

class Players* pPlayers;
Players* g_Players(){ return pPlayers; }

// TODO just for debug
Model2d* cursor;
Players::Players() : Component(){
	pPlayers = this;
	// TODO just for debug
	for (int i = 0; i < MAX_PLAYERS; i++){
		playerModels[i] = new PlayerModel();
		playerModels[i]->Create();
	}
	cursor=new Model2d();
	cursor->AddQuad(quad2(-0.0625f, -0.0625f, 0.125f, 0.125f), g_Graphics()->m_Resources->gameCursor[0]);
	cursor->texture = g_Graphics()->m_Resources->textureGame;
	cursor->Create();
}
Players::~Players(){
	for(int i=0;i<MAX_PLAYERS;i++){
		delete playerModels[i];
	}
	delete cursor;
	pPlayers = NULL;
}
///TODO: debug only
bool lastSpaceState=false;
void Players::Input(unsigned char* keys,int xrel,int yrel,int wheel){
	if(wheel>0){
		for(int i=0;i<MAX_PLAYERS;i++){
			g_World()->players[i]->weapon++;
			g_World()->players[i]->weapon = g_World()->players[i]->weapon%NUM_WEAPONS;
		}
	}else if(wheel<0){
		for(int i=0;i<MAX_PLAYERS;i++){
			g_World()->players[i]->weapon--;
			if(g_World()->players[i]->weapon==-1) g_World()->players[i]->weapon+=NUM_WEAPONS;
		}
	}
	if(keys[SDL_SCANCODE_KP_8]){
		g_World()->players[0]->rot.x += 0.4f*g_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_2]){
		g_World()->players[0]->rot.x -= 0.4f*g_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_4]){
		g_World()->players[0]->rot.z += 0.4f*g_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_6]){
		g_World()->players[0]->rot.z -= 0.4f*g_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_7]){
		g_World()->players[0]->rot.y -= 0.4f*g_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_KP_9]){
		g_World()->players[0]->rot.y += 0.4f*g_Client()->tickCoeff;
	}
	if(keys[SDL_SCANCODE_SPACE]){
		if(!lastSpaceState){
			for(int i=0;i<MAX_PLAYERS;i++)
				g_World()->players[i]->vel.y=g_World()->players[i]->vel.y>0?0:1;
			lastSpaceState=true;
		}
	}else{
		lastSpaceState=false;
	}
}
void Players::StateChange(STATE lastState){}
void Players::Render(){
	for(int i=0;i<MAX_PLAYERS;i++){
		playerModels[i]->Update(g_World()->players[i]);
		playerModels[i]->Render();
	}
}
void Players::Render2d(){
	cursor->Render();
}
void Players::RenderBillboard(){
	for(int i=0;i<MAX_PLAYERS;i++){
		playerModels[i]->RenderBillboard();
	}
}
void Players::Tick(){}
void Players::Message(int type,char* value){}
