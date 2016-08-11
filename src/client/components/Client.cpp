#include "Client.h"

#include <shared/Console.h>
#include <shared/System.h>                   //TODO: remove
#include <client/components/Resources.h>     //TODO: remove
#include <client/components/Map.h>
#include <client/components/Camera.h>        //TODO: remove
#include <client/components/UI.h>
#include <client/components/Input.h>
#include <client/components/ui/Label.h>       //TODO: remove
#include <client/components/ui/Panel.h>       //TODO: remove
#include <client/components/ui/Layout.h>      //TODO: remove
#include <client/components/graphics/shaders/ShaderShadow.h> //TODO: remove
#include <client/components/graphics/shaders/Shader3dComposer.h>     //TODO: remove
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
}
Client::~Client() {
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	pClient = NULL;
}
Panel *scene;
Panel *depthMap;
Label *fps;
Player *localPlayer;
void Client::Start() {
	working = true;
	state.ingame = true;

	g_Map()->Load("1234");
	auto skin = g_Resources()->skinTextures.end();
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (skin == g_Resources()->skinTextures.end())
			skin = g_Resources()->skinTextures.begin();
		g_World()->players[i] = new Player(i);
		Player *player = g_World()->players[i];
		player->nickname = g_World()->players[i]->skin = (*skin).first;
		player->pos = glm::vec3(rand() % 4080, rand() % 4080, 400.0);
		player->weapon = rand() % NUM_WEAPONS;
		player->emote = rand() % NUM_EMOTES;
		player->rot = rot3(rand() * M_PI / RAND_MAX * 2, rand() * M_PI / RAND_MAX * 2,
		                   rand() * M_PI / RAND_MAX * 2);
		skin++;
	}
	localPlayer = g_World()->players[0];
	// localPlayer->color = glm::vec4(0, 0, 0, 0.3f);
	g_Shader3dComposer();
	depthMap =  new Panel(g_ShaderShadow()->shadowMap);
	depthMap->size = glm::vec2(0.5f, 0.5f);
	g_UI()->screenLayout->Add(depthMap);
	fps = new Label("FPS: 60", FONT_BIG);
	fps->align = glm::uvec2(ALIGN_RIGHT, ALIGN_TOP);
	g_UI()->screenLayout->Add(fps);
	scene = new Panel(*g_Shader3dComposer(), FLIP_Y);
	g_UI()->screenLayout->Add(scene);
}
void Client::Stop() {
	g_UI()->screenLayout->Remove(scene);
	g_UI()->screenLayout->Remove(fps);
	g_UI()->screenLayout->Remove(depthMap);
	delete depthMap;
	delete fps;
	delete scene;
	working = false;
};
bool Client::isRunning() { return working; }
void Client::Tick() {
	if (oldstate != ClientComponent::state)
		ClientComponent::StateChangeComponents(oldstate);
	oldstate = ClientComponent::state;

	fps->SetText("FPS: " + std::to_string((int)(1.0f / g_System()->tickCoeff)), FONT_BIG);
	if (g_Input()->mouseWheel > 0) {
		localPlayer->weapon++;
		localPlayer->weapon %= NUM_WEAPONS;
		localPlayer->emote++;
		localPlayer->emote %= NUM_EMOTES;
	}
	if (g_Input()->mouseWheel < 0) {
		localPlayer->weapon += NUM_WEAPONS;
		localPlayer->weapon--;
		localPlayer->weapon %= NUM_WEAPONS;
		localPlayer->emote += NUM_EMOTES;
		localPlayer->emote--;
		localPlayer->emote %= NUM_EMOTES;
	}
	localPlayer->dir = glm::vec2(0, 0);
	if ((g_Input()->keyboard[SDLK_w] && g_Camera()->up.z > 0) ||
	    (g_Input()->keyboard[SDLK_s] && g_Camera()->up.z < 0)) {
		localPlayer->dir.x += g_Camera()->look.x;
		localPlayer->dir.y += g_Camera()->look.y;
	}
	if ((g_Input()->keyboard[SDLK_s] && g_Camera()->up.z > 0) ||
	    (g_Input()->keyboard[SDLK_w] && g_Camera()->up.z < 0)) {
		localPlayer->dir.x -= g_Camera()->look.x;
		localPlayer->dir.y -= g_Camera()->look.y;
	}
	if (g_Input()->keyboard[SDLK_d]) {
		localPlayer->dir.x += g_Camera()->right.x;
		localPlayer->dir.y += g_Camera()->right.y;
	}
	if (g_Input()->keyboard[SDLK_a]) {
		localPlayer->dir.x -= g_Camera()->right.x;
		localPlayer->dir.y -= g_Camera()->right.y;
	}
	if (!glm::zero(localPlayer->dir))
		localPlayer->dir = glm::normalize(localPlayer->dir);
	localPlayer->jump = g_Input()->keyboard[SDLK_SPACE];
	localPlayer->hook = g_Input()->mouse[SDL_BUTTON_RIGHT];
	localPlayer->look = g_Camera()->rot;
	localPlayer->local = true;
	g_Camera()->pos = localPlayer->pos;

	if (g_Input()->keyboard[SDLK_RIGHT])
		localPlayer->pos += (float)(g_System()->tickCoeff * 300) * g_Camera()->right;
	if (g_Input()->keyboard[SDLK_LEFT])
		localPlayer->pos -= (float)(g_System()->tickCoeff * 300) * g_Camera()->right;
	if (g_Input()->keyboard[SDLK_UP])
		localPlayer->pos += (float)(g_System()->tickCoeff * 300) * g_Camera()->look;
	if (g_Input()->keyboard[SDLK_DOWN])
		localPlayer->pos -= (float)(g_System()->tickCoeff * 300) * g_Camera()->look;

	if (g_Input()->keyboard[SDLK_F1])
		for (int i = 1; i < MAX_PLAYERS; i++) {
			int id = rand() % (MAX_PLAYERS - 1) + 1;
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
