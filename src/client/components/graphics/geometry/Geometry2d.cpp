#include "Geometry2d.h"

void Geometry2d::Clear() {
	v.clear();
	t.clear();
}
void Geometry2d::Push(const glm::vec2 &v, const glm::vec2 &t) {
	this->v.push_back(v);
	this->t.push_back(t);
}
void Geometry2d::Push(const std::vector<glm::vec2> &v,
                      const std::vector<glm::vec2> &t) {
	this->v.insert(this->v.end(), v.begin(), v.end());
	this->t.insert(this->t.end(), t.begin(), t.end());
}
Geometry2d Geometry2d::operator+(const Geometry2d &geom) {
	Geometry2d v = *this;
	v += geom;
	return v;
}
Geometry2d &Geometry2d::operator+=(const Geometry2d &geom) {
	Push(geom.v, geom.t);
	return *this;
}
Geometry2d::Geometry2d(Geometry2d &geom) { (*this) = geom; }
Geometry2d::Geometry2d(Geometry2d &&geom) { (*this) = std::move(geom); }
Geometry2d &Geometry2d::operator=(Geometry2d &geom) {
	this->v = geom.v;
	this->t = geom.t;
	return *this;
}
Geometry2d &Geometry2d::operator=(Geometry2d &&geom) {
	this->v = std::move(geom.v);
	this->t = std::move(geom.t);
	return *this;
}
