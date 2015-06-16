#ifndef MAP_H
#define MAP_H


#include <vector>
#include <string>
#include "../Component.h"
#include "../../tools/Tile.h"
#include "../../../other/sdl/include/SDL.h"
#include "../../../other/glew/include/glew.h"
#define GLM_FORCE_RADIANS
#include "../../../other/glm/gtc/matrix_transform.hpp"
#include "../../../other/glm/gtc/type_ptr.hpp"

using namespace std;
class Model;
class Tile;

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
	///<summary>Buffer tile has tile above it?</summary>
	///<returns>true if has, false otherwise</param>
	bool hasTop();
	///<summary>Buffer tile has tile bellow it?</summary>
	///<returns>true if has, false otherwise</param>
	bool hasBot();
	///<summary>Buffer tile has tile left it?</summary>
	///<returns>true if has, false otherwise</param>
	bool hasLeft();
	///<summary>Buffer tile has tile right it?</summary>
	///<returns>true if has, false otherwise</param>
	bool hasRight();
	///<summary>Buffer tile has tile at the front of it?</summary>
	///<returns>true if has, false otherwise</param>
	bool hasY();
	///<summary>Buffer tile has tile at the back of it?</summary>
	///<returns>true if has, false otherwise</param>
	bool hasy();

	///<summary>Model object</summary>
	class Model* m_Model;
	///<summary>Size of the map</summary>
	int sizex;
	///<summary>Size of the map</summary>
	int sizey;
	///<summary>Size of the map</summary>
	int sizez;
	///<summary>Vector of the tiles sorted by id</summary>
	std::vector<Tile> tilesById;
	///<summary>Array of the tiles sorted by position</summary>
	Tile**** tilesByPos;
	///<summary>Texture of the map</summary>
	GLuint texture;

	///<summary>Buffer tile</summary>
	Tile* buffer;
};
Map* g_Map();

#endif
