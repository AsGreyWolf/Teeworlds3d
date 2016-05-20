#ifndef TILE_H
#define TILE_H

#include <vector>
#include <tools/vmath.h>

class Tile {
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
	Tile() {
		hasx = false;
		hasX = false;
		hasy = false;
		hasY = false;
		hasz = false;
		hasZ = false;
	}
	bool isPhys() const { return isPhys(type); }
	bool isNoHook() const { return isNoHook(type); }
	bool isVisible() const { return isVisible(type); }
	static bool isPhys(int type) { return (type == 1 || type == 2); }
	static bool isNoHook(int type) { return type == 2; }
	static bool isVisible(int type) { return isPhys(type); }
};

#endif
