#ifndef QUAD3_H
#define QUAD3_H

#include <cmath>
#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/closest_point.hpp>
#include <gtx/rotate_vector.hpp>
#include <tools/quad2.h>

namespace tee3d {
class quad3 {
public:
	glm::vec3 p1, p2, p3, p4;
	quad3(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3,
	      const glm::vec3 &v4) {
		p1 = v1;
		p2 = v2;
		p3 = v3;
		p4 = v4;
	}
	explicit quad3(const quad2 &data, float depth = 0) {
		p1 = glm::vec3(-data.v00().x, depth, data.v00().y);
		p2 = glm::vec3(-data.v10().x, depth, data.v10().y);
		p3 = glm::vec3(-data.v11().x, depth, data.v11().y);
		p4 = glm::vec3(-data.v01().x, depth, data.v01().y);
	}
	quad3(const quad3 &second) = default;
	quad3(quad3 &&second) noexcept = default;
	quad3 &operator=(const quad3 &second) = default;
	quad3 &operator=(quad3 &&second) noexcept = default;
	quad3 operator*(float a) const {
		return quad3(p1 * a, p2 * a, p3 * a, p4 * a);
	}
	quad3 operator/(float a) const { return operator*(1.0f / a); }
	quad3 operator+(const glm::vec3 &c) const {
		return quad3(p1 + c, p2 + c, p3 + c, p4 + c);
	}
	quad3 operator-(const glm::vec3 &c) const { return operator+(-c); }
};
};

#endif
