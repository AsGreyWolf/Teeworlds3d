#ifndef GEOMETRY3D_H
#define GEOMETRY3D_H

#include <tools/vmath.h>
#include <vector>

struct Geometry3d {
	Geometry3d(){};
	Geometry3d(Geometry3d &geom);
	Geometry3d(Geometry3d &&geom);
	std::vector<glm::vec3> v;
	std::vector<glm::vec3> n;
	std::vector<glm::vec2> t;
	void Clear();
	void Push(const glm::vec3 &v, const glm::vec3 &n, const glm::vec2 &t);
	void Push(const std::vector<glm::vec3> &v, const std::vector<glm::vec3> &n,
	          const std::vector<glm::vec2> &t);
	Geometry3d operator+(const Geometry3d &geom);
	Geometry3d &operator+=(const Geometry3d &geom);
	Geometry3d &operator=(Geometry3d &geom);
	Geometry3d &operator=(Geometry3d &&geom);
};

#endif
