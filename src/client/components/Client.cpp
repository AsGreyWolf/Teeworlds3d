#include "Client.h"

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <shared/Console.h>
#include <shared/System.h>               //TODO: remove
#include <client/components/Graphics.h>  //TODO: remove
#include <client/components/Resources.h> //TODO: remove
#include <client/components/Map.h>       //TODO: remove
#include <client/components/Camera.h>    //TODO: remove
#include <client/components/Input.h>
#include <client/components/graphics/models/Model3d.h>       //TODO: remove
#include <client/components/graphics/models/PlayerModel.h>   //TODO: remove
#include <client/components/graphics/models/Model2d.h>       //TODO: remove
#include <client/components/graphics/shaders/ShaderShadow.h> //TODO: remove
#include <client/components/graphics/geometry/Primitives.h>  //TODO: remove
#include <shared/World.h>                                    //TODO: remove

class Client *pClient;
Client *g_Client() { return pClient ? pClient : new Client(); }

STATE oldstate;
int main(int argc, char *argv[]) {
	SDL_SetMainReady();
	SDL_Init(0);
	oldstate = ClientComponent::state;
	g_Client()->Start();
	while (g_Client()->isRunning()) {
		ClientComponent::TickComponents();
	}
	ClientComponent::ClearComponents();
	SDL_Quit();
	return 0;
}

Client::Client() : ClientComponent() {
	pClient = this;
	SDL_version ver;
	if (SDL_Init(SDL_INIT_EVENTS) != 0) {
		g_Console()->Err("Unable to initialize SDL Events: " +
		                 std::string(SDL_GetError()));
		return; // TODO: need exceptions
	}
	SDL_GetVersion(&ver);
	g_Console()->Info("Initialized SDL Events " + std::to_string(ver.major) + "." +
	                  std::to_string(ver.minor) + "." + std::to_string(ver.patch));
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		g_Console()->Err("Unable to initialize SDL_IMG: " +
		                 std::string(IMG_GetError()));
		return; // TODO: need exceptions
	}
	ver = *IMG_Linked_Version();
	g_Console()->Info("Initialized SDL_IMG " + std::to_string(ver.major) + "." +
	                  std::to_string(ver.minor) + "." + std::to_string(ver.patch));
	if (TTF_Init() != 0) {
		g_Console()->Err("Unable to initialize SDL_TTF: " +
		                 std::string(TTF_GetError()));
		return; // TODO: need exceptions
	}
	ver = *TTF_Linked_Version();
	g_Console()->Info("Initialized SDL_TTF " + std::to_string(ver.major) + "." +
	                  std::to_string(ver.minor) + "." + std::to_string(ver.patch));
}
Client::~Client() {
	TTF_Quit();
	IMG_Quit();
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	pClient = NULL;
}
Model2d *depthMap;
void Client::Start() {
	g_Map()->Load("1234");
	working = true;
	state.ingame = true;
	auto skin = g_Resources()->skinTextures.end();
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (skin == g_Resources()->skinTextures.end())
			skin = g_Resources()->skinTextures.begin();
		g_World()->players[i] = new Player(i);
		g_World()->players[i]->nickname = g_World()->players[i]->skin = (*skin).first;
		g_World()->players[i]->pos = glm::vec3(rand() % 3200, rand() % 3200, 400.0);
		g_World()->players[i]->weapon = rand() % NUM_WEAPONS;
		g_World()->players[i]->emote = rand() % NUM_EMOTES;
		g_World()->players[i]->rot =
		    rot3(rand() * M_PI / RAND_MAX * 2, rand() * M_PI / RAND_MAX * 2,
		         rand() * M_PI / RAND_MAX * 2);
		skin++;
	}
	g_World()->players[0]->color = glm::vec4(0, 0, 0, 0.3f);

	depthMap = new Model2d();
	depthMap->position =
	    g_Graphics()->screen.p00 + g_Graphics()->screen.p11 * 0.25f;
	depthMap->texture = g_ShaderShadow()->texture;
	depthMap->Add(Quad(g_Graphics()->screen / 4, quad2(0, 0, 1, 1)));
	depthMap->Enable();
}
void Client::Stop() { working = false; }
bool Client::isRunning() { return working; }
void Client::Tick() {
	if (oldstate != ClientComponent::state)
		ClientComponent::StateChangeComponents(oldstate);
	oldstate = ClientComponent::state;

	if (g_Input()->mouseWheel > 0) {
		g_World()->players[0]->weapon++;
		g_World()->players[0]->weapon %= NUM_WEAPONS;
		g_World()->players[0]->emote++;
		g_World()->players[0]->emote %= NUM_EMOTES;
	}
	if (g_Input()->mouseWheel < 0) {
		g_World()->players[0]->weapon += NUM_WEAPONS;
		g_World()->players[0]->weapon--;
		g_World()->players[0]->weapon %= NUM_WEAPONS;
		g_World()->players[0]->emote += NUM_EMOTES;
		g_World()->players[0]->emote--;
		g_World()->players[0]->emote %= NUM_EMOTES;
	}
	g_World()->players[0]->dir = glm::vec2(0, 0);
	if ((g_Input()->keyboard[SDLK_w] && g_Camera()->up.z > 0) ||
	    (g_Input()->keyboard[SDLK_s] && g_Camera()->up.z < 0)) {
		g_World()->players[0]->dir.x += g_Camera()->look.x;
		g_World()->players[0]->dir.y += g_Camera()->look.y;
	}
	if ((g_Input()->keyboard[SDLK_s] && g_Camera()->up.z > 0) ||
	    (g_Input()->keyboard[SDLK_w] && g_Camera()->up.z < 0)) {
		g_World()->players[0]->dir.x -= g_Camera()->look.x;
		g_World()->players[0]->dir.y -= g_Camera()->look.y;
	}
	if (g_Input()->keyboard[SDLK_d]) {
		g_World()->players[0]->dir.x += g_Camera()->right.x;
		g_World()->players[0]->dir.y += g_Camera()->right.y;
	}
	if (g_Input()->keyboard[SDLK_a]) {
		g_World()->players[0]->dir.x -= g_Camera()->right.x;
		g_World()->players[0]->dir.y -= g_Camera()->right.y;
	}
	if (!glm::zero(g_World()->players[0]->dir))
		g_World()->players[0]->dir = glm::normalize(g_World()->players[0]->dir);
	g_World()->players[0]->jump = g_Input()->keyboard[SDLK_SPACE];
	g_World()->players[0]->hook = g_Input()->mouse[SDL_BUTTON_RIGHT];
	g_World()->players[0]->look = g_Camera()->rot;
	g_World()->players[0]->local = true;
	g_Camera()->pos = g_World()->players[0]->pos;
	if (g_Input()->keyboard[SDLK_F1])
		for (int i = 1; i < MAX_PLAYERS; i++) {
			int id = 0; // rand() % (MAX_PLAYERS - 1) + 1;
			g_World()->players[i]->hookState = HOOK_FLYING;
			g_World()->players[i]->hookDir =
			    glm::normalize(g_World()->players[id]->pos - g_World()->players[i]->pos);
			g_World()->players[i]->hookPos = g_World()->players[i]->pos;
			g_World()->players[i]->hookedPlayer = -1;
			g_World()->players[i]->hookTime = g_System()->GetTime();
		}
	if (g_Input()->keyboard[SDLK_F2])
		for (int i = 1; i < MAX_PLAYERS; i++)
			g_World()->players[i]->hookState = HOOK_IDLE;
	if (g_Input()->quit)
		Stop();
}
