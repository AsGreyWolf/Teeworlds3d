#ifndef SHPERE_H
#define SHPERE_H

#include <client/components/graphics/geometry/Geometry3d.h>

class Sphere {
public:
	Sphere();
	Sphere &SetRadius(float radius);
	Sphere &SetPosition(const glm::vec3 &position);
	Sphere &SetTexCoord(const quad2 &texcoord);
	Sphere &SetRings(int rings);
	Sphere &SetSectors(int sectors);
	Sphere &SetScale(const glm::vec3 &scale);
	Sphere &SetReversed(bool reversed);
	operator Geometry3d();

private:
	float radius;
	glm::vec3 position;
	quad2 texcoord;
	int rings;
	int sectors;
	glm::vec3 scale;
	bool reversed;
};

#endif
