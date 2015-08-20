#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include <string>
#include "../../other/sdl/include/SDL.h"
#include "Component.h"

using namespace std;

///<summary>Main loop component</summary>
class Client : public Component{
public:
	///<summary>Creates all the components and gamecycle</summary>
	Client();
	~Client();
	///<summary>Stores input to components</summary>
	///<param name="keys">Keyboard state</param>
	///<param name="xrel">Mouse X position change</param>
	///<param name="yrel">Mouse Y position change</param>
	///<param name="wheel">Mouse wheel state</param>
	void Input(unsigned char* keys,int xrel,int yrel,int wheel);
	///<summary>Render 3d</summary>
	void Render();
	///<summary>Render 3d Billboard</summary>
	void RenderBillboard();
	///<summary>Render 2d</summary>
	void Render2d();
	///<summary>Tick the components</summary>
	void Tick();
	///<summary>Send message to the components</summary>
	void Message(int type,char* value);
	///<summary>Send new state to the components</summary>
	///<param name="lastState">Last state</param>
	void StateChange(STATE lastState);

	///<summary>Starts the gamecycle</summary>
	void Start();
	///<summary>Stops the gamecycle</summary>
	void Stop();
	///<summary>Is gamecycle running?</summary>
	///<returns>true if it is, false otherwise</returns>
	static bool isRunning();

	///<summary>All the components</summary>
	std::vector <Component*> m_Components;
	std::vector <SharedComponent*> m_SharedComponents;
	
	///<summary>Current State</summary>
	STATE state;
	SDL_Window *screen;
private:
	static bool working;
	SDL_Renderer* renderer;
};
Client* g_Client();

#endif
