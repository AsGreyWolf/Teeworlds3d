#ifndef QUAD2_H
#define QUAD2_H

#include <algorithm>
#include <cmath>
#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/closest_point.hpp>

class quad2 {
public:
	glm::vec2 pos;
	glm::vec2 size;
	float &x, &y, &w, &h;
	quad2(const glm::vec2 &p, const glm::vec2 &s)
	    : pos(p), size(s), x(pos.x), y(pos.y), w(size.x), h(size.y) {}
	quad2(float x, float y, float w, float h) : quad2(glm::vec2(x, y), glm::vec2(w, h)){};
	quad2(const quad2 &second) : quad2(second.pos, second.size){};
	quad2& operator=(const quad2 &second) {
		pos = second.pos;
		size = second.size;
		return *this;
	};
	quad2() : quad2(0, 0, 0, 0){};
	glm::vec2 v00() const {
		return glm::vec2(x, y);
	}
	glm::vec2 v01() const {
		return glm::vec2(x, y + h);
	}
	glm::vec2 v10() const {
		return glm::vec2(x + w, y);
	}
	glm::vec2 v11() const {
		return glm::vec2(x + w, y + h);
	}
	quad2 operator>>(const glm::vec2 &c) const {
		float x = std::min(pos.x, c.x);
		float y = std::min(pos.y, c.y);
		float w = std::max(pos.x + size.x, c.x) - x;
		float h = std::max(pos.y + size.y, c.y) - y;
		return quad2(x, y, w, h);
	}
	quad2 operator>>(const quad2 &c) const { return operator>>(c.v00()) >> c.v11(); }
	quad2 reflectX() const { return quad2(x + w, y, -w, h); }
	quad2 reflectY() const { return quad2(x, y + h, w, -h); }
	quad2 operator*(float a) const {
		return quad2(x, y, w * a, h * a);
	}
	quad2 operator/(float a) const { return operator*(1.0f / a); }
	quad2 operator+(const glm::vec2 &c) const {
		return quad2(pos + c, size);
	}
	quad2 operator-(const glm::vec2 &c) const { return operator+(-c); }
	bool contains(const glm::vec2 &c) const { return c.x >= x && c.x < x + w && c.y >= y && c.y < y + h; }
};
#endif
