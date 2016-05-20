#ifndef POSITIONED_H
#define POSITIONED_H

#include <tools/vmath.h>

class Positioned {
public:
	///<summary>Position on map</summary>
	glm::vec3 pos;
	///<summary>Rotation(rads)</summary>
	rot3 rot;
	inline void LookAt(const glm::vec3 &to, const float *fixedX = NULL,
	                   const float *fixedY = NULL, const float *fixedZ = NULL) {
		rot3 buffer = rot3(to - pos);
		if (fixedX)
			buffer.x = *fixedX;
		if (fixedY)
			buffer.y = *fixedY;
		if (fixedZ) {
			float z = *fixedZ;
			if ((buffer.z < z - M_PI_2 || buffer.z > z + M_PI_2) &&
			    (buffer.z < z - M_PI_2 + 2 * M_PI || buffer.z > z + M_PI_2 + 2 * M_PI) &&
			    (buffer.z < z - M_PI_2 - 2 * M_PI || buffer.z > z + M_PI_2 - 2 * M_PI))
				buffer.x = -buffer.x;
			buffer.z = z;
		}
		rot = buffer;
	};
};

#endif
