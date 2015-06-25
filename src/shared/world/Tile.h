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
	bool isPhysTile(){
		return isPhys(type);
	}
	bool isNoHook(){
		return isNoHook(type);
	}
	static bool isPhys(int type3){
		return (type3 == 1 || type3 == 2);
	}
	static bool isNoHook(int type3){
		return type3 == 2;
	}
};



#endif