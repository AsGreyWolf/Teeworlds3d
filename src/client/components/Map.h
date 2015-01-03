#ifndef MAP_H
#define MAP_H


#include <vector>
#include <string>
#include "../Component.h"
#include "../../tools/Tile.h"
#include "../../../other/sdl/include/SDL.h"
#include "../../../other/glew/include/glew.h"
#include "../../../other/glm/gtc/matrix_transform.hpp"
#include "../../../other/glm/gtc/type_ptr.hpp"

using namespace std;
class Model;
class Tile;

///<summary>Map component</summary>
class Map : public Component{
public:

	///<summary>Stores 'c' to 'm_Client'</summary>
	Map(Client* c) : Component(c){};

	///<summary>Initialization callback</summary>
	///<returns>true if all right, false if error found</returns>
	bool OnInit();
	///<summary>Input callback</summary>
	///<param name="keys">Keyboard state</param>
	///<param name="xrel">Mouse X position change</param>
	///<param name="yrel">Mouse Y position change</param>
	///<param name="wheel">Mouse wheel state</param>
	void OnInput(unsigned char* keys,int xrel,int yrel,int wheel);
	///<summary>State change callback</summary>
	///<param name="lastState">Last state</param>
	void OnStateChange(STATE lastState);
	///<summary>Quit callback</summary>
	void OnQuit();
	///<summary>3d render callback</summary>
	void OnRender();
	///<summary>Render 3d Billboard</summary>
	void OnRenderBillboard();
	///<summary>2d render callback</summary>
	void OnRender2d();
	///<summary>Tick callback</summary>
	void OnTick();
	///<summary>System message callback</summary>
	void OnMessage(int type,char* value);

	///<summary>Loads the map</summary>
	///<param name="name">Filename in data/maps folder</param>
	bool Load(string name);
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

#endif