#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include <string>
#include "../../other/sdl/include/SDL.h"
#include "Component.h"

using namespace std;
class Graphics;
class Camera;
class Map;
class Players;
class GUI;

class Client : public Component{
public:
	///<summary>Stores 'c' to 'm_Client', creates all the components and gamecycle</summary>
	Client() : Component(this){ Constructor(); };
	///<summary>Tries to initialize components</summary>
	///<returns>true if all right, false if error found</returns>
	bool OnInit();
	///<summary>Stores input to components</summary>
	///<param name="keys">Keyboard state</param>
	///<param name="xrel">Mouse X position change</param>
	///<param name="yrel">Mouse Y position change</param>
	///<param name="wheel">Mouse wheel state</param>
	void OnInput(unsigned char* keys,int xrel,int yrel,int wheel);
	///<summary>Quit</summary>
	void OnQuit();
	///<summary>Render 3d</summary>
	void OnRender();
	///<summary>Render 2d</summary>
	void OnRender2d();
	///<summary>Tick the components</summary>
	void OnTick();
	///<summary>Send message to the components</summary>
	void OnMessage(int type,char* value);
	///<summary>Send new state to the components</summary>
	///<param name="lastState">Last state</param>
	void OnStateChange(STATE lastState);

	///<summary>creates all the components and gamecycle</summary>
	void Constructor();
	///<summary>Starts the gamecycle</summary>
	void Start();
	///<summary>Stops the gamecycle</summary>
	void Stop();
	///<summary>Is gamecycle running?</summary>
	///<returns>true if it is, false otherwise</returns>
	static bool isRunning();
	///<summary>Send error message</summary>
	///<param name="c">Message</param>
	static void Err(string c);
	///<summary>Send info message</summary>
	///<param name="c">Message</param>
	static void Info(string c);
	///<summary>Get filename in data folder</summary>
	///<param name="str">Filename</param>
	string GetDataFile(string str);

	///<summary>All the components</summary>
	std::vector <Component*> m_Components;
	///<summary>Graphics component</summary>
	class Graphics* m_Graphics;
	///<summary>Camera component</summary>
	class Camera* m_Camera;
	///<summary>Map component</summary>
	class Map* m_Map;
	///<summary>Players component</summary>
	class Players* m_Players;
	///<summary>GUI component</summary>
	class GUI* m_GUI;
	///<summary>Current frames</summary>
	static int frames;
	int fps;
	float tickCoeff;
	long lasttickTime;
	///<summary>Current State</summary>
	STATE state;
	SDL_Window *screen;
private:
	static bool working;
	SDL_Renderer* renderer;
	string PATH_CUR;
	string PATH_DATA;
};
Uint32 calcFPS(Uint32 interval, void *param);

#endif
