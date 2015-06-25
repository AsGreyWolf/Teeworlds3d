#ifndef MAP_H
#define MAP_H


#include <vector>
#include <string>
#include "../Component.h"
#include "../../../other/sdl/include/SDL.h"
#include "../../../other/glew/include/glew.h"
#define GLM_FORCE_RADIANS
#include "../../../other/glm/gtc/matrix_transform.hpp"
#include "../../../other/glm/gtc/type_ptr.hpp"

using namespace std;
class Model;

///<summary>Map as game object</summary>
class Map : public Component{
public:
	Map();
	~Map();

	///<summary>Input callback</summary>
	///<param name="keys">Keyboard state</param>
	///<param name="xrel">Mouse X position change</param>
	///<param name="yrel">Mouse Y position change</param>
	///<param name="wheel">Mouse wheel state</param>
	void Input(unsigned char* keys,int xrel,int yrel,int wheel);
	///<summary>State change callback</summary>
	///<param name="lastState">Last state</param>
	void StateChange(STATE lastState);
	///<summary>3d render callback</summary>
	void Render();
	///<summary>Render 3d Billboard</summary>
	void RenderBillboard();
	///<summary>2d render callback</summary>
	void Render2d();
	///<summary>Tick callback</summary>
	void Tick();
	///<summary>System message callback</summary>
	void Message(int type,char* value);

	///<summary>Loads the map</summary>
	///<param name="name">Filename in data/maps folder</param>
	bool Load(string name);
	void UnLoad();

	///<summary>Model object</summary>
	class Model* m_Model;
	///<summary>Texture of the map</summary>
	GLuint texture;
};
Map* g_Map();

#endif
