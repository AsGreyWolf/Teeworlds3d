#ifndef GEOMETRY2D_H
#define GEOMETRY2D_H

#include <tools/vmath.h>
#include <vector>

struct Geometry2d {
	Geometry2d(){};
	Geometry2d(Geometry2d &geom);
	Geometry2d(Geometry2d &&geom);
	Geometry2d &operator=(Geometry2d &geom);
	Geometry2d &operator=(Geometry2d &&geom);
	Geometry2d operator+(const Geometry2d &geom);
	Geometry2d &operator+=(const Geometry2d &geom);
	void Push(const glm::vec2 &v, const glm::vec2 &t);
	void Push(const std::vector<glm::vec2> &v, const std::vector<glm::vec2> &t);
	void Clear();
	std::vector<glm::vec2> v;
	std::vector<glm::vec2> t;
};

#endif
