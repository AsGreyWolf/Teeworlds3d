#ifndef POSITIONED_H
#define POSITIONED_H

#include <tools/vmath.h>

namespace tee3d {
class positioned {
public:
	///<summary>Position on map</summary>
	glm::vec3 pos;
	///<summary>Rotation(rads)</summary>
	rot3 rot;
	inline void LookAt(const glm::vec3 &to, const float *fixedX = nullptr,
	                   const float *fixedY = nullptr,
	                   const float *fixedZ = nullptr) {
		rot3 buffer = rot3(to - pos);
		if (fixedX != nullptr) {
			buffer.x = *fixedX;
		}
		if (fixedY != nullptr) {
			buffer.y = *fixedY;
		}
		if (fixedZ != nullptr) {
			float z = *fixedZ;
			if ((buffer.z < z - M_PI_2 || buffer.z > z + M_PI_2) &&
			    (buffer.z < z - M_PI_2 + 2 * M_PI || buffer.z > z + M_PI_2 + 2 * M_PI) &&
			    (buffer.z < z - M_PI_2 - 2 * M_PI || buffer.z > z + M_PI_2 - 2 * M_PI)) {
				buffer.x = -buffer.x;
			}
			buffer.z = z;
		}
		rot = buffer;
	};
};
};

#endif
