#include "Player.h"
#include "../World.h"

Player::Player(int id){
	this->id = id;
	pos = glm::vec3(0, 0, 0);
	rot=glm::vec3(0,0,0);
	vel = glm::vec3(0, 0, 0);
	acc = glm::vec2(0, 0);

	color = glm::vec4(0, 0, 0, 0);
	int weapon=0;
	int emote=0;

	std::string skin="";
	std::string nickname="";
};