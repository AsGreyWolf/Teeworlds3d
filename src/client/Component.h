#ifndef COMPONENT_H
#define COMPONENT_H

#include "../shared/SharedComponent.h"

///<summary>Client state</summary>
struct STATE{
	const  bool operator!=(const STATE s){
		return ingame!=s.ingame;
	}
	bool ingame;
};
///<summary>Component which may be used only on Client side</summary>
class Component : public SharedComponent{
public:
	Component():SharedComponent(){};
	virtual ~Component(){};
	///<summary>Stores input to components</summary>
	///<param name="keys">Keyboard state</param>
	///<param name="xrel">Mouse X position change</param>
	///<param name="yrel">Mouse Y position change</param>
	///<param name="wheel">Mouse wheel state</param>
	virtual void Input(unsigned char* keys,int xrel,int yrel,int wheel){};
	///<summary>Render 3d</summary>
	virtual void Render(){};
	///<summary>Render 3d Billboard</summary>
	virtual void RenderBillboard(){};
	///<summary>Render 2d</summary>
	virtual void Render2d(){};
	///<summary>Tick the components</summary>
	virtual void Tick(){};
	///<summary>Send message to the components</summary>
	virtual void Message(int type,char* value){};
	///<summary>Send new state to the components</summary>
	///<param name="lastState">Last state</param>
	virtual void StateChange(STATE lastState){};
};

#endif
