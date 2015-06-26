#ifndef TILE_H
#define TILE_H
#include <vector>
#include "../../../other/glm/glm.hpp"

class Tile
{
public:
	int x;
	int y;
	int z;
	int id;
	int type;
	int texTop;
	int texBottom;
	int texOther;
	bool hasx;
	bool hasX;
	bool hasy;
	bool hasY;
	bool hasz;
	bool hasZ;
	Tile(){
		hasx = true;
		hasX = true;
		hasy = true;
		hasY = true;
		hasz = true;
		hasZ = true;
	}
	bool isPhys(){
		return isPhys(type);
	}
	bool isNoHook(){
		return isNoHook(type);
	}
	bool isVisible(){
		return isVisible(type);
	}
	static bool isPhys(int type){
		return (type == 1 || type == 2);
	}
	static bool isNoHook(int type){
		return type == 2;
	}
	static bool isVisible(int type){
		return isPhys(type);
	}
};



#endif