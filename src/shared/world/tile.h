#ifndef TILE_H
#define TILE_H

#include <tools/protocol.h>
#include <tools/vmath.h>
#include <vector>

namespace tee3d {
namespace shared {
class tile {
public:
	int x;
	int y;
	int z;
	int id;
	tile_type_t type;
	int texTop;
	int texBottom;
	int texOther;
	bool hasx = false;
	bool hasX = false;
	bool hasy = false;
	bool hasY = false;
	bool hasz = false;
	bool hasZ = false;
	bool phys() const { return type == 1 || type == 2; }
	bool no_hook() const { return type == 2; }
	bool visible() const { return phys(); }
};
};
};

#endif
