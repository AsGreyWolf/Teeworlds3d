#ifndef PLAYER_H
#define PLAYER_H
#include "../tools/Protocol.h"
#include "../../other/glm/glm.hpp"
#include <string>
#define MAX_PLAYERS 16
class Player{
public:
	Player(){
		//Hook_Pos=vec3(0,0,0);
		//Hook_Dir=vec3(0,1,0);
		//HookState=HOOK_STATE.IDLE;
		//HookedPlayer=-1;
		//animwalking=false;
		//Jumped=0;
		//Jump=false;
		//Hook=false;
		pos=glm::vec3(0,0,0);
		dir=glm::vec3(0,1,0);

		color=glm::vec4(0,0,0,0);
		vel=glm::vec3(0,0,0);
		weapon=WEAPON_HUMMER;
		emote=EMOTE_NORMAL;
		//texture=-1;
		//local=false;
		//inAir=false;
	};
	//vec3 Hook_Pos;
	//vec3 Hook_Dir;
	//int HookTick;
	//HOOK_STATE HookState;
	//int HookedPlayer;
	int id;
	//int TriggeredEvents;
	//bool animwalking;
	//int Jumped;
	//bool Jump;
	//bool Hook;
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 vel;

	glm::vec4 color;
	int weapon;
	int emote;
	//unsigned int texture;
	//bool local;
	std::string skin;
	std::string NickName;
	//bool inAir
};

#endif
