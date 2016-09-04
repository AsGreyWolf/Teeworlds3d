#include "Geometry3d.h"

void Geometry3d::Clear() {
	v.clear();
	n.clear();
	t.clear();
}
void Geometry3d::Push(const glm::vec3 &v, const glm::vec3 &n,
                      const glm::vec2 &t) {
	this->v.push_back(v);
	this->n.push_back(n);
	this->t.push_back(t);
}
void Geometry3d::Push(const std::vector<glm::vec3> &v,
                      const std::vector<glm::vec3> &n,
                      const std::vector<glm::vec2> &t) {
	this->v.insert(this->v.end(), v.begin(), v.end());
	this->n.insert(this->n.end(), n.begin(), n.end());
	this->t.insert(this->t.end(), t.begin(), t.end());
}
Geometry3d Geometry3d::operator+(const Geometry3d &geom) {
	Geometry3d v = *this;
	v += geom;
	return v;
}
Geometry3d &Geometry3d::operator+=(const Geometry3d &geom) {
	Push(geom.v, geom.n, geom.t);
	return *this;
}
Geometry3d::Geometry3d(Geometry3d &geom) { (*this) = geom; }
Geometry3d::Geometry3d(Geometry3d &&geom) { (*this) = std::move(geom); }
Geometry3d &Geometry3d::operator=(Geometry3d &geom) {
	this->v = geom.v;
	this->n = geom.n;
	this->t = geom.t;
	return *this;
}
Geometry3d &Geometry3d::operator=(Geometry3d &&geom) {
	this->v = std::move(geom.v);
	this->n = std::move(geom.n);
	this->t = std::move(geom.t);
	return *this;
}
