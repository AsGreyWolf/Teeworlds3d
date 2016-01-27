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
class Texture;

///<summary>Map as game object</summary>
class Map : public Component{
public:
	Map();
	~Map();

	///<summary>State change callback</summary>
	///<param name="lastState">Last state</param>
	void StateChange(const STATE& lastState);
	///<summary>Tick callback</summary>
	void Tick();

	///<summary>Loads the map</summary>
	///<param name="name">Filename in data/maps folder</param>
	bool Load(const string& name);
	void UnLoad();
private:
	///<summary>Model object</summary>
	class Model* m_Model;
	///<summary>Texture of the map</summary>
	Texture* texture;
};
Map* g_Map();

#endif
