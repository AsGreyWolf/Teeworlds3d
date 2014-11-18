#ifndef QUAD3_H
#define QUAD3_H
#include "../../other/glm/glm.hpp"
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
};

#endif