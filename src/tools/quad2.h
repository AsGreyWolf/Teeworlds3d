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
	glm::vec2 p00, p01, p10, p11;
	quad2(const glm::vec2 &s00, const glm::vec2 &s10, const glm::vec2 &s01,
	      const glm::vec2 &s11) {
		p00 = s00;
		p01 = s01;
		p10 = s10;
		p11 = s11;
	};
	quad2(const glm::vec2 &pos, float w, float h)
	    : quad2(pos, pos + glm::vec2(w, 0), pos + glm::vec2(0, h),
	            pos + glm::vec2(w, h)) {}
	quad2(float x, float y, float w, float h) : quad2(glm::vec2(x, y), w, h){};
	quad2(const quad2 &second)
	    : quad2(second.p00, second.p10, second.p01, second.p11) {}
	quad2() : quad2(0, 0, 0, 0){};
	quad2 &operator=(const quad2 &second) {
		p00 = second.p00;
		p01 = second.p01;
		p10 = second.p10;
		p11 = second.p11;
		return (*this);
	}
	quad2 operator>>(const glm::vec2 &c) const {
		float x = std::min(p00.x, c.x);
		float y = std::min(p00.y, c.y);
		float x1 = std::max(p11.x, c.x);
		float y1 = std::max(p11.y, c.y);
		return quad2(x, y, x1 - x, y1 - y);
	}
	quad2 operator>>(const quad2 &c) const { return operator>>(c.p00) >> c.p11; }
	quad2 reflectX() const { return quad2(p10, p00, p11, p01); }
	quad2 reflectY() const { return quad2(p01, p11, p00, p10); }
	quad2 operator*(float a) const {
		return quad2(p00 * a, p10 * a, p01 * a, p11 * a);
	}
	quad2 operator/(float a) const { return operator*(1.0f / a); }
	quad2 operator+(const glm::vec2 &c) const {
		return quad2(p00 + c, p10 + c, p01 + c, p11 + c);
	}
	quad2 operator-(const glm::vec2 &c) const { return operator+(-c); }
};
#endif
