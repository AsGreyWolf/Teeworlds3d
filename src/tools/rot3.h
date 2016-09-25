#ifndef ROT3_H
#define ROT3_H

#include <algorithm>
#include <cmath>
#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/closest_point.hpp>
#include <gtx/rotate_vector.hpp>

class rot3 {
public:
	float &x, &y, &z;
	rot3() : x(data.x), y(data.y), z(data.z){};
	rot3(const rot3 &other) : x(data.x), y(data.y), z(data.z) {
		data = other.data;
	};
	rot3(float x, float y, float z) : x(data.x), y(data.y), z(data.z) {
		data = glm::vec3(x, y, z);
	};
	explicit rot3(const glm::vec3 &v) : x(data.x), y(data.y), z(data.z) {
		glm::vec2 xy = glm::normalize(glm::vec2(v.x, v.y));
		data = glm::vec3(asin(glm::normalize(v).z), 0,
		                 xy.x > 0.0 ? -acos(xy.y) : acos(xy.y));
	};
	rot3 &operator=(const rot3 &other) {
		data = other.data;
		return *this;
	};

	rot3 operator+() const {
		rot3 second;
		second.data = +data;
		return second;
	};
	rot3 operator-() const {
		rot3 second;
		second.data = -data;
		return second;
	};
	rot3 operator+(const rot3 &second) const {
		rot3 third;
		third.data = data + second.data;
		return third;
	};
	rot3 operator-(const rot3 &second) const { return operator+(-second); };
	rot3 operator*(float second) const {
		rot3 third;
		third.data = data * second;
		return third;
	};
	rot3 operator/(float second) const { return operator*(1 / second); };
	bool operator==(const rot3 &other) const { return data == other.data; };
	bool operator!=(const rot3 &other) const { return data != other.data; };

private:
	glm::vec3 data;
};

#endif
