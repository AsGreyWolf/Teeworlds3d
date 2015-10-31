#include "Client.h"
#include <iostream>
#include <locale>
#include <clocale>
#include "components/Graphics.h"
#include "components/Camera.h"
#include "components/Map.h"
#include "components/Players.h"
#include "components/GUI.h"
#include "../shared/System.h"
#include "../shared/Console.h"
#include "../shared/World.h"
#include "../../other/sdl/include/SDL_ttf.h"

class Client* pClient;
Client* g_Client(){ return pClient; }

bool Client::working=false;

int main(int argc, char *argv[])
{
	pClient = new Client();
	pClient->Start();
	STATE startstate;
	startstate.ingame=false;
	pClient->state.ingame = true;
	pClient->StateChange(startstate);
	while (pClient->isRunning()){
		STATE oldstate = pClient->state;
		pClient->Input(NULL, 0, 0, 0);
		pClient->Tick();
		if (oldstate != pClient->state) pClient->StateChange(oldstate);
	}
	delete pClient;
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
Client::Client():Component(){
	m_SharedComponents.push_back((SharedComponent*)new System());
	m_SharedComponents.push_back((SharedComponent*)new Console());
	pClient = this;

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS)!=0)
	{
		Console::Err("Unable to initialize SDL Client components: " + string(SDL_GetError()));
		return; //TODO: need exceptions
	}
	SDL_version ver;
	if(TTF_Init()!=0)
	{
		Console::Err("Unable to initialize SDL_TTF: " + string(TTF_GetError()));
		return; //TODO: TODO: need exceptions
	}
	ver=*TTF_Linked_Version();
	Console::Info("Initialized SDL_TTF " + to_string(ver.major) + "." + to_string(ver.minor) + "." + to_string(ver.patch));
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,2);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if ((screen = SDL_CreateWindow("",50, 50, 1024, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)) == NULL)
	{
		Console::Err("Could not create window: " + string(SDL_GetError()));
		return; //need exceptions
	}
	if ((renderer = SDL_CreateRenderer(screen, -1, 0)) == NULL)
	{
		Console::Err("Could not get renderer: " + string(SDL_GetError()));
		return; //TODO: need exceptions
	}
	Component* graphics = new Graphics();
	m_SharedComponents.push_back((SharedComponent*)new World());//TODO debug only
	m_Components.push_back((Component*)new Camera());
	m_Components.push_back((Component*)new Map());
	m_Components.push_back((Component*)new Players());
	m_Components.push_back((Component*)new GUI());
	m_Components.push_back(graphics);
}
Client::~Client(){
	reverse(m_Components.begin(), m_Components.end());
	for (auto &component : m_Components){
		delete component;
	}
	m_Components.clear();
	reverse(m_SharedComponents.begin(), m_SharedComponents.end());
	for (auto &component : m_SharedComponents){
		delete component;
	}
	m_SharedComponents.clear();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	TTF_Quit();
	SDL_Quit();
}
void Client::Input(unsigned char* keyss,int xrels,int yrels,int wheels){
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
				if(xrel>100000)xrel=0;
				if(yrel>100000)yrel=0;
				break;
			case SDL_MOUSEWHEEL:
				wheel=sdlevent.wheel.y;
				break;
		}
	}
	keys = SDL_GetKeyboardState(NULL);
	for(auto &component : m_Components){
		component->Input((unsigned char*)keys,xrel,yrel,wheel);
	}
}
void Client::Render(){
	for(auto &component : m_Components){
		component->Render();
	}
}
void Client::RenderBillboard(){
	for(auto &component : m_Components){
		component->RenderBillboard();
	}
}
void Client::Render2d(){
	for(auto &component : m_Components){
		component->Render2d();
	}
}
void Client::Tick(){
	for (auto &component : m_SharedComponents){
		component->Tick();
	}
	for(auto &component : m_Components){
		component->Tick();
	}
	SDL_GL_SwapWindow(screen);
}
void Client::Message(int type,char* value){
	for(auto &component : m_Components){
		component->Message(type,value);
	}
}
void Client::StateChange(STATE lastState){
	for(auto &component : m_Components){
		component->StateChange(lastState);
	}
}
