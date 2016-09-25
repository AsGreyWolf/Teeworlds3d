#ifndef VMATH_H
#define VMATH_H

#define _USE_MATH_DEFINES
#include <cmath>
#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/closest_point.hpp>
#include <gtx/rotate_vector.hpp>
#include <tools/quad2.h>
#include <tools/quad3.h>
#include <tools/rot3.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2 1.57079632679
#endif

namespace glm {
template <typename genType> GLM_FUNC_DECL inline bool zero(genType const &x) {
	return abs(x) < 1e-8;
};
template <> GLM_FUNC_DECL inline bool zero(vec2 const &x) {
	return zero(x.x) && zero(x.y);
};
template <> GLM_FUNC_DECL inline bool zero(vec3 const &x) {
	return zero(x.x) && zero(x.y) && zero(x.z);
};
template <> GLM_FUNC_DECL inline bool zero(vec4 const &x) {
	return zero(x.x) && zero(x.y) && zero(x.z) && zero(x.w);
};
GLM_FUNC_DECL inline bool one(vec2 const &x) { return zero(x - vec2(1, 1)); };
GLM_FUNC_DECL inline bool one(vec3 const &x) {
	return zero(x - vec3(1, 1, 1));
};
GLM_FUNC_DECL inline bool one(vec4 const &x) {
	return zero(x - vec4(1, 1, 1, 1));
};
GLM_FUNC_DECL inline vec3 rotate(vec3 const &x, rot3 const &r) {
	vec3 y = x;
	y = rotateY(y, r.y);
	y = rotateX(y, r.x);
	y = rotateZ(y, r.z);
	return y;
};
template <typename genType>
GLM_FUNC_DECL inline float sqr_distance(genType const &x, genType const &x2) {
	return dot(x - x2, x - x2);
};
} // namespace glm

#endif
