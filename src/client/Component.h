#ifndef COMPONENT_H
#define COMPONENT_H

#include <stdint.h>

class Client;
struct STATE{
	const  bool operator!=(const STATE s){
		return ingame!=s.ingame;
	}
	bool ingame;
};
class Component{
public:
	///<summary>Client class</summary>
	class Client* m_Client;
	///<summary>Stores 'c' to 'm_Client', creates all the components and gamecycle</summary>
	Component(Client* mClient){
		m_Client=mClient;
	};
	~Component(){};
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
