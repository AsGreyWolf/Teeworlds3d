#include "Client.h"
#include <iostream>
#include <locale>
#include <clocale>
#include "components/graphics/Resources.h"
#include "components/Graphics.h"
#include "components/Camera.h"
#include "components/Map.h"
#include "components/Players.h"
#include "components/GUI.h"
#include "../shared/System.h"
#include "../shared/Console.h"
#include "../shared/world/player.h"
#include "../shared/World.h"
#include "../../other/sdl/include/SDL_ttf.h"
#include "../../other/sdl/include/SDL_image.h"

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
	SharedComponent::RegisterComponent(new System());
	SharedComponent::RegisterComponent(new Console());
	SharedComponent::RegisterComponent(new World());
	pClient = this;

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS)!=0)
	{
		Console::Err("Unable to initialize SDL Client components: " + string(SDL_GetError()));
		return; //TODO: need exceptions
	}
	SDL_version ver;
	/*if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		Console::Err("Unable to initialize SDL_IMG: " + string(IMG_GetError()));
		return; //TODO: TODO: need exceptions
	}
	ver = *IMG_Linked_Version();
	Console::Info("Initialized SDL_IMG " + to_string(ver.major) + "." + to_string(ver.minor) + "." + to_string(ver.patch));*/
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
	Component::RegisterComponent(new Graphics());
	Component::RegisterComponent(new Camera());
	Component::RegisterComponent(new Map());
	Component::RegisterComponent((Component*)new Players());
	Component::RegisterComponent((Component*)new GUI());


	//TODO: only debug
	auto skinName = g_Graphics()->m_Resources->skinTextures.begin();
	for (glm::uint8_t i = 0; i<MAX_PLAYERS; i++) {
		g_World()->players[i] = new Player(i);
		g_World()->players[i]->pos = vec3(0, 0, rand() % 20048);//vec3(rand() % 2048, rand() % 2048, rand() % 2048);
		g_World()->players[i]->rot = vec3(rand() / (static_cast <float> (RAND_MAX / (M_PI * 2))), rand() / (static_cast <float> (RAND_MAX / (M_PI * 2))), rand() / (static_cast <float> (RAND_MAX / (M_PI * 2))));
		g_World()->players[i]->rot = glm::normalize(g_World()->players[i]->rot);
		g_World()->players[i]->weapon = rand() % NUM_WEAPONS;
		g_World()->players[i]->emote = EMOTE_NORMAL;
		g_World()->players[i]->skin = (*skinName).first;
		g_World()->players[i]->nickname = (*skinName).first;
		skinName++;
		if (skinName == g_Graphics()->m_Resources->skinTextures.end()) skinName = g_Graphics()->m_Resources->skinTextures.begin();
		if (i == 0 || i == MAX_PLAYERS - 1) continue;
		g_World()->players[i]->hookState = HOOK_GRABBED;
		g_World()->players[i]->hookedPlayer = i + 1;
	}
}
Client::~Client(){
	Component::ClearComponents();
	SharedComponent::ClearComponents();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
void Client::Input(unsigned char* keyss,int xrels,int yrels,int wheels){
	Component::Input(keyss, xrels, yrels, wheels);
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
	Component::InputComponents((unsigned char*)keys, xrel, yrel, wheel);
}
void Client::Tick(){
	Component::Tick();
	SharedComponent::TickComponents();
	SDL_GL_SwapWindow(screen);
}
void Client::Message(int type,char* value){
	Component::Message(type,value);
	Component::MessageComponents(type,value);
}
void Client::StateChange(const STATE& lastState){
	Component::StateChange(lastState);
	Component::StateChangeComponents(lastState);
}
