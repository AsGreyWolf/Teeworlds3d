#include "Client.h"
#include <iostream>
#include <locale>
#include <clocale>
#include "components/Graphics.h"
#include "components/Camera.h"
#include "components/Map.h"
#include "components/Players.h"
#include "components/GUI.h"
#include "../tools/system.h"
#include "../../other/sdl/include/SDL_ttf.h"

class Client* mp_Client;
Client* Component::m_Client(){ return mp_Client; }

bool Client::working=false;
int Client::frames=0;

int main(int argc, char *argv[])
{
	/*std::setlocale(LC_ALL, "");
	std::locale l("");
	std::locale::global(l);
	std::cout.imbue(l);
	std::cerr.imbue(l);
	std::clog.imbue(l);

	std::wcout.imbue(l);
	std::wcerr.imbue(l);
	std::wclog.imbue(l);
	std::ios::sync_with_stdio(false);*/
	mp_Client = new Client();
	mp_Client->Start();
	STATE startstate;
	startstate.ingame=false;
	mp_Client->state.ingame = true;
	mp_Client->StateChange(startstate);
	while (mp_Client->isRunning()){
		long tickTime=System::GetTime();
		mp_Client->tickCoeff = (tickTime - mp_Client->lasttickTime)*1.0 / 1000;
		mp_Client->lasttickTime = tickTime;
		STATE oldstate = mp_Client->state;
		mp_Client->Input(NULL, 0, 0, 0);
		mp_Client->Tick();
		if (oldstate != mp_Client->state) mp_Client->StateChange(oldstate);
	}
	delete mp_Client;
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
	mp_Client = this;
	System::Init();
	System::GetPath(PATH_CUR);
	PATH_DATA=PATH_CUR+"data/";
	fps=60;

	if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
	{
		Err("Unable to initialize SDL: "+string(SDL_GetError()));
		return; //TODO: need exceptions
	}
	SDL_version ver;
	SDL_GetVersion(&ver);
	Info("Initialized SDL "+to_string(ver.major)+"."+to_string(ver.minor)+"."+to_string(ver.patch));
	if(TTF_Init()!=0)
	{
		Err("Unable to initialize SDL_TTF: "+string(TTF_GetError()));
		return; //TODO: TODO: need exceptions
	}
	ver=*TTF_Linked_Version();
	Info("Initialized SDL_TTF "+to_string(ver.major)+"."+to_string(ver.minor)+"."+to_string(ver.patch));
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,2);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if ((screen = SDL_CreateWindow("",50, 50, 1024, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)) == NULL)
	{
		Err("Could not create window: "+string(SDL_GetError()));
		return; //need exceptions
	}
	if ((renderer = SDL_CreateRenderer(screen, -1, 0)) == NULL)
	{
		Err("Could not get renderer: "+string(SDL_GetError()));
		return; //TODO: need exceptions
	}
	m_Components.push_back((Component*)new Graphics());
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
void Client::Err(string c){
	std::cerr << "[ERROR] " << c << std::endl;
};
void Client::Info(string c){
	std::cout << "[INFO] " << c << std::endl;
};

Uint32 calcFPS(Uint32 interval, void *param){
	if(!Client::isRunning()) return interval;
	Client::Info("FPS = "+to_string(Client::frames));
	if (mp_Client != NULL)
		mp_Client->fps = Client::frames;
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
