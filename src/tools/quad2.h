#ifndef QUAD2_H
#define QUAD2_H
#include "../../other/glm/glm.hpp"
#include <algorithm>
class quad2{
public:
	glm::vec2 p00,p01,p10,p11;
	quad2(glm::vec2 pos,float w,float h){
		p00=pos;
		p01=pos+glm::vec2(0,h);
		p10=pos+glm::vec2(w,0);
		p11=pos+glm::vec2(w,h);
	}
	quad2(float x,float y,float w,float h){
		p00=glm::vec2(x,y);
		p01=glm::vec2(x,y+h);
		p10=glm::vec2(x+w,y);
		p11=glm::vec2(x+w,y+h);
	};
	quad2(glm::vec2 s00,glm::vec2 s10,glm::vec2 s01,glm::vec2 s11){
		p00=s00;
		p01=s01;
		p10=s10;
		p11=s11;
	};
	quad2(){
		p00=glm::vec2(0,0);
		p01=glm::vec2(0,0);
		p10=glm::vec2(0,0);
		p11=glm::vec2(0,0);
	}
	quad2 operator>>(const quad2& c){
		float x=std::min(p00.x,c.p00.x);
		float y=std::min(p00.y,c.p00.y);
		float x1=std::max(p11.x,c.p11.x);
		float y1=std::max(p11.y,c.p11.y);
		return quad2(x,y,x1-x,y1-y);
	}
	quad2 reflectX(){
		return quad2(p10,p00,p11,p01);
	}
	quad2 reflectY(){
		return quad2(p01,p11,p00,p10);
	}
	quad2 operator*(float a){
		return quad2(p00*a,p10*a,p01*a,p11*a);
	}
	quad2 operator/(float a){
		return operator*(1.0f/a);
	}
	quad2 operator+(const glm::vec2& c){
		return quad2(p00+c,p10+c,p01+c,p11+c);
	}
	quad2 operator-(const glm::vec2& c){
		return operator+(-c);
	}
	quad2 operator>>(const glm::vec2& c){
		return operator>>(operator+(c));
	}
	static glm::vec3 vec2rot(glm::vec3 v){
		glm::vec2 xy=glm::normalize(glm::vec2(v.x,v.y));
		return glm::vec3(asin(v.z),0,xy.x>0.0?-acos(xy.y):acos(xy.y));
	}
	static glm::vec3 vec2vec3(glm::vec2 v, float depth=0){
		return glm::vec3(-v.x, depth, v.y);
	}
};
#endif