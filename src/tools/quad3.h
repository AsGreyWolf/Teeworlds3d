#ifndef QUAD3_H
#define QUAD3_H
#include "../../other/glm/glm.hpp"
#include "quad2.h"
using namespace glm;
class quad3{
public:
	vec3 p1,p2,p3,p4;
	quad3(vec3 v1,vec3 v2,vec3 v3,vec3 v4){
		p1=v1;
		p2=v2;
		p3=v3;
		p4=v4;
	}
	quad3(quad2 data, float depth=0){
		p2 = quad2::vec2vec3(data.p10, depth);
		p1 = quad2::vec2vec3(data.p00, depth);
		p4 = quad2::vec2vec3(data.p01, depth);
		p3 = quad2::vec2vec3(data.p11, depth);
	}
	quad3 operator*(float a){
		return quad3(p1*a,p2*a,p3*a,p4*a);
	}
};

#endif