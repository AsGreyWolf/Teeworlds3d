#include "Players.h"
#include <cstdlib>
#include "graphics/models/Model2d.h"
#include "graphics/models/PlayerModel.h"
#include "graphics/Resources.h"
#include "Graphics.h"
#include "Camera.h"
#include "../Client.h"
#include "../../shared/World.h"
#include "../../shared/world/Player.h"
#include "../../shared/System.h"

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
	if (keys[SDL_SCANCODE_KP_6])
		g_World()->players[0]->pos += (float)(g_System()->tickCoeff * 300)*g_Camera()->right;
	if (keys[SDL_SCANCODE_KP_4])
		g_World()->players[0]->pos -= (float)(g_System()->tickCoeff * 300)*g_Camera()->right;
	if (keys[SDL_SCANCODE_KP_8])
		g_World()->players[0]->pos += (float)(g_System()->tickCoeff * 300)*g_Camera()->look;
	if (keys[SDL_SCANCODE_KP_2])
		g_World()->players[0]->pos -= (float)(g_System()->tickCoeff * 300)*g_Camera()->look;
	if(wheel>0){
		for(int i=0;i<MAX_PLAYERS;i++){
			g_World()->players[i]->weapon++;
			if (g_World()->players[i]->weapon == NUM_WEAPONS) g_World()->players[i]->weapon = 0;
		}
	}else if(wheel<0){
		for(int i=0;i<MAX_PLAYERS;i++){
			if (g_World()->players[i]->weapon==0) g_World()->players[i]->weapon = NUM_WEAPONS;
			g_World()->players[i]->weapon--;
		}
	}
	glm::vec2 cameraFront = vec2(g_Camera()->look.x, g_Camera()->look.y);
	glm::vec2 cameraRight = vec2(g_Camera()->right.x, g_Camera()->right.y);
	g_World()->players[0]->acc = vec2(0, 0);
	if (keys[SDL_SCANCODE_W]) g_World()->players[0]->acc += cameraFront;
	if (keys[SDL_SCANCODE_S]) g_World()->players[0]->acc -= cameraFront;
	if (keys[SDL_SCANCODE_D]) g_World()->players[0]->acc += cameraRight;
	if (keys[SDL_SCANCODE_A]) g_World()->players[0]->acc -= cameraRight;
	if(glm::length(g_World()->players[0]->acc)>0)
		g_World()->players[0]->acc = glm::normalize(g_World()->players[0]->acc);
	g_World()->players[0]->jump = false;
	if(keys[SDL_SCANCODE_SPACE]){
		if(!lastSpaceState){
			g_World()->players[0]->jump = true;
			lastSpaceState=true;
		}
	}else{
		lastSpaceState=false;
	}
	g_World()->players[0]->look = g_Camera()->rotation;
	g_World()->players[0]->controls = true;
}
void Players::StateChange(STATE lastState){}
void Players::Render(){
	for(int i=0;i<MAX_PLAYERS;i++){
		playerModels[i]->Update(g_World()->players[i]);
		((Model*)playerModels[i])->Render();
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
void Players::Tick(){
	g_Camera()->position = g_World()->players[0]->pos;
}
void Players::Message(int type,char* value){}
