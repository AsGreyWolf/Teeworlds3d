#ifndef PLAYERS_H
#define PLAYERS_H

#include <vector>
#include "../Component.h"
#include "../../tools/Protocol.h"

class PlayerModel;

///<summary>Players as game objects</summary>
class Players : Component{
public:
	Players();
	~Players();
	///<summary>Input callback</summary>
	///<param name="keys">Keyboard state</param>
	///<param name="xrel">Mouse X position change</param>
	///<param name="yrel">Mouse Y position change</param>
	///<param name="wheel">Mouse wheel state</param>
	void Input(unsigned char* keys,int xrel,int yrel,int wheel) override;
	///<summary>Tick callback</summary>
	void Tick() override;
private:
	///<summary>Players array</summary>
	PlayerModel* playerModels[MAX_PLAYERS];
};
Players* g_Players();

#endif