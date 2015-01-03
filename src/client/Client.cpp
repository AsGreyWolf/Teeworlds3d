#include "Client.h"
#include <iostream>
#include <cstring>
#include "components/Graphics.h"
#include "components/Camera.h"
#include "components/Map.h"
#include "components/Players.h"
#include "components/GUI.h"
#include "../tools/system.h"
#include "../../other/sdl/include/SDL_ttf.h"

class Client* instanse;
bool Client::working=false;
int Client::frames=0;
int main(int argc, char *argv[])
{
	new Client();
	return 0;
}
void Client::Start(){
	working=true;
}
void Client::Stop(){
	working=false;
}
bool Client::isRunning(){
	return working;
}
void Client::Constructor(){
	instanse=this;
	System::Init();
	PATH_CUR=new char[System::MAX_FILENAME];
	PATH_DATA=new char[System::MAX_FILENAME];
	System::GetPath(PATH_CUR);
	PATH_DATA=PATH_CUR+"/data/";
	fps=60;
	m_Graphics=new Graphics(this);
	m_Camera=new Camera(this);
	m_Map=new Map(this);
	m_Players=new Players(this);
	m_GUI=new GUI(this);
	m_Components.push_back((Component*)m_Graphics);
	m_Components.push_back((Component*)m_Camera);
	m_Components.push_back((Component*)m_Map);
	m_Components.push_back((Component*)m_Players);
	m_Components.push_back((Component*)m_GUI);
	if(OnInit()){
		Start();
		STATE startstate;
		startstate.ingame=false;
		state.ingame=true;
		OnStateChange(startstate);
		while(isRunning()){
			long tickTime=System::GetTime();
			tickCoeff=(tickTime-lasttickTime)/16.6666666666666666667f;
			lasttickTime=tickTime;
			STATE oldstate=state;
			OnInput(NULL,0,0,0);
			OnTick();
			if(oldstate!=state) OnStateChange(oldstate);
		}
	}
	OnQuit();
}
bool Client::OnInit(){
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)!=0)
	{
		char c[256];
		sprintf(c,"Unable to initialize SDL: %s",SDL_GetError());
		Err(c);
		return false;
	}
	if(TTF_Init()!=0)
	{
		char c[256];
		sprintf(c,"Unable to initialize SDL_TTF: %s",TTF_GetError());
		Err(c);
		return false;
	}
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,2);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if ((screen = SDL_CreateWindow("",50, 50, 1024, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)) == NULL)
	{
		char c[256];
		sprintf(c,"Could not create window: %s",SDL_GetError());
		Err(c);
		return false;
	}
	if ((renderer = SDL_CreateRenderer(screen, -1, 0)) == NULL)
	{
		char c[256];
		sprintf(c,"Could not get renderer: %s", SDL_GetError());
		Err(c);
		return false;
	}

	for(auto &component : m_Components){
		if(!component->OnInit()) return false;
	}

	void* calcFPS_param;
	SDL_TimerID my_timer_id = SDL_AddTimer(1000, calcFPS, calcFPS_param);

	return true;
}
void Client::OnInput(unsigned char* keyss,int xrels,int yrels,int wheels){
	SDL_Event sdlevent;
	const Uint8* keys = NULL;
	int xrel=0;
	int yrel=0;
	int wheel=0;
	while( SDL_PollEvent( &sdlevent ) )
	{
		switch( sdlevent.type ) {
			case SDL_QUIT:
				Stop();
				break;
			case SDL_MOUSEMOTION:
				xrel=sdlevent.motion.xrel;
				yrel=sdlevent.motion.yrel;
				break;
			case SDL_MOUSEWHEEL:
				wheel=sdlevent.wheel.y;
				break;
		}
	}
	keys = SDL_GetKeyboardState(NULL);
	for(auto &component : m_Components){
		component->OnInput((unsigned char*)keys,xrel,yrel,wheel);
	}
}
void Client::OnQuit(){
	for(auto &component : m_Components){
		component->OnQuit();
	}
	TTF_Quit();
	SDL_Quit();
}
void Client::OnRender(){
	for(auto &component : m_Components){
		component->OnRender();
	}
}
void Client::OnRenderBillboard(){
	for(auto &component : m_Components){
		component->OnRenderBillboard();
	}
}
void Client::OnRender2d(){
	for(auto &component : m_Components){
		component->OnRender2d();
	}
}
void Client::OnTick(){
	for(auto &component : m_Components){
		component->OnTick();
	}
	SDL_GL_SwapWindow(screen);
	frames++;
}
void Client::OnMessage(int type,char* value){
	for(auto &component : m_Components){
		component->OnMessage(type,value);
	}
}
void Client::Err(string c){
	std::cerr << "[ERROR] " << c << std::endl;
};
void Client::Info(string c){
	std::cout << "[INFO] " << c << std::endl;
};

Uint32 calcFPS(Uint32 interval, void *param){
	if(!Client::isRunning()) return interval;
	char c[256];
	sprintf(c,"FPS = %d", Client::frames);
	Client::Info(c);
	if(instanse!=NULL)
		instanse->fps=Client::frames;
	Client::frames=0;
	return interval;
}
string Client::GetDataFile(string str){
	return PATH_DATA+str;
}
void Client::OnStateChange(STATE lastState){
	for(auto &component : m_Components){
		component->OnStateChange(lastState);
	}
}
