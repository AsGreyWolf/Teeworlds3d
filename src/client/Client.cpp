#include "Client.h"
#include <iostream>
#include <locale>
#include <clocale>
#include "../shared/Console.h"
#include "../shared/World.h"
#include "components/Graphics.h"
#include "components/Camera.h"
#include "components/Map.h"
#include "components/Players.h"
#include "components/GUI.h"
#include "../tools/system.h"
#include "../../other/sdl/include/SDL_ttf.h"

class Client* pClient;
Client* g_Client(){ return pClient; }

bool Client::working=false;
int Client::frames=0;

int main(int argc, char *argv[])
{
	pClient = new Client();
	pClient->Start();
	STATE startstate;
	startstate.ingame=false;
	pClient->state.ingame = true;
	pClient->StateChange(startstate);
	while (pClient->isRunning()){
		long tickTime=System::GetTime();
		pClient->tickCoeff = (tickTime - pClient->lasttickTime)*1.0 / 1000;
		pClient->lasttickTime = tickTime;
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
	pClient = this;
	System::Init();
	System::GetPath(PATH_CUR);
	PATH_DATA=PATH_CUR+"data/";
	fps=60;

	if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
	{
		Console::Err("Unable to initialize SDL: " + string(SDL_GetError()));
		return; //TODO: need exceptions
	}
	SDL_version ver;
	SDL_GetVersion(&ver);
	Console::Info("Initialized SDL " + to_string(ver.major) + "." + to_string(ver.minor) + "." + to_string(ver.patch));
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

	m_SharedComponents.push_back((SharedComponent*)new Console());
	

	m_Components.push_back((Component*)new Graphics());
	m_SharedComponents.push_back((SharedComponent*)new World());//TODO debug only
	m_Components.push_back((Component*)new Camera());
	m_Components.push_back((Component*)new Map());
	m_Components.push_back((Component*)new Players());
	m_Components.push_back((Component*)new GUI());

	SDL_AddTimer(1000, calcFPS, NULL);
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
	frames++;
}
void Client::Message(int type,char* value){
	for(auto &component : m_Components){
		component->Message(type,value);
	}
}

Uint32 calcFPS(Uint32 interval, void *param){
	if(!Client::isRunning()) return interval;
	Console::Info("FPS = " + to_string(Client::frames));
	if (pClient != NULL)
		pClient->fps = Client::frames;
	Client::frames=0;
	return interval;
}
string Client::GetDataFile(string str){
	return PATH_DATA+str;
}
void Client::StateChange(STATE lastState){
	for(auto &component : m_Components){
		component->StateChange(lastState);
	}
}
