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
	///<summary>Initialization callback</summary>
	///<returns>true if all right, false if error found</returns>
	virtual bool OnInit(){return true;};
	///<summary>Stores input to components</summary>
	///<param name="keys">Keyboard state</param>
	///<param name="xrel">Mouse X position change</param>
	///<param name="yrel">Mouse Y position change</param>
	///<param name="wheel">Mouse wheel state</param>
	virtual void OnInput(unsigned char* keys,int xrel,int yrel,int wheel){};
	///<summary>Quit</summary>
	virtual void OnQuit(){};
	///<summary>Render 3d</summary>
	virtual void OnRender(){};
	///<summary>Render 3d Billboard</summary>
	virtual void OnRenderBillboard(){};
	///<summary>Render 2d</summary>
	virtual void OnRender2d(){};
	///<summary>Tick the components</summary>
	virtual void OnTick(){};
	///<summary>Send message to the components</summary>
	virtual void OnMessage(int type,char* value){};
	///<summary>Send new state to the components</summary>
	///<param name="lastState">Last state</param>
	virtual void OnStateChange(STATE lastState){};
};

#endif