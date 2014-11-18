#include "Rectangle.h"
#include "../Graphics.h"

Rectangle::Rectangle(Graphics* g,quad2 in,quad2 out):Model2d(g){
	quad2 tex(0,0,1,1);
	addQuad(in,tex);
	float roundedleft=(in.p00-out.p00).x;
	float roundedbottom=(in.p00-out.p00).y;
	float roundedright=(out.p11-in.p11).x;
	float roundedtop=(out.p11-in.p11).y;
	addQuad(quad2(in.p01,in.p11,out.p01+vec2(roundedleft,0),out.p11-vec2(roundedright,0)),tex);
	addQuad(quad2(out.p00+vec2(roundedleft,0),out.p10-vec2(roundedright,0),in.p00,in.p10),tex);
	addQuad(quad2(out.p00+vec2(0,roundedbottom),in.p00,out.p01-vec2(0,roundedtop),in.p01),tex);
	addQuad(quad2(in.p10,out.p10+vec2(0,roundedbottom),in.p11,out.p11-vec2(0,roundedtop)),tex);

	if(glm::min(roundedright,roundedtop)!=0){
		int quality=m_Graphics->to_pixels(glm::max(roundedright,roundedtop))/4;

		for(int i=0;i<quality;i++){
			addVertex(in.p11+vec2(cos(i*M_PI_2/quality)*roundedright,sin(i*M_PI_2/quality)*roundedtop),vec2(0,0));
			addVertex(in.p11,vec2(0,0));
			addVertex(in.p11+vec2(cos((i+1)*M_PI_2/quality)*roundedright,sin((i+1)*M_PI_2/quality)*roundedtop),vec2(0,0));
		}
	}
	if(glm::min(roundedright,roundedbottom)!=0){
		int quality=m_Graphics->to_pixels(glm::max(roundedright,roundedbottom))/4;
		for(int i=0;i<quality;i++){
			addVertex(in.p10+vec2(cos(i*M_PI_2/quality)*roundedright,-sin(i*M_PI_2/quality)*roundedbottom),vec2(0,0));
			addVertex(in.p10,vec2(0,0));
			addVertex(in.p10+vec2(cos((i+1)*M_PI_2/quality)*roundedright,-sin((i+1)*M_PI_2/quality)*roundedbottom),vec2(0,0));
		}
	}
	if(glm::min(roundedleft,roundedbottom)!=0){
		int quality=m_Graphics->to_pixels(glm::max(roundedleft,roundedbottom))/4;
		for(int i=0;i<quality;i++){
			addVertex(in.p00+vec2(-cos(i*M_PI_2/quality)*roundedleft,-sin(i*M_PI_2/quality)*roundedbottom),vec2(0,0));
			addVertex(in.p00,vec2(0,0));
			addVertex(in.p00+vec2(-cos((i+1)*M_PI_2/quality)*roundedleft,-sin((i+1)*M_PI_2/quality)*roundedbottom),vec2(0,0));
		}
	}
	if(glm::min(roundedleft,roundedtop)!=0){
		int quality=m_Graphics->to_pixels(glm::max(roundedleft,roundedtop))/4;
		for(int i=0;i<quality;i++){
			addVertex(in.p01+vec2(-cos(i*M_PI_2/quality)*roundedleft,sin(i*M_PI_2/quality)*roundedtop),vec2(0,0));
			addVertex(in.p01,vec2(0,0));
			addVertex(in.p01+vec2(-cos((i+1)*M_PI_2/quality)*roundedleft,sin((i+1)*M_PI_2/quality)*roundedtop),vec2(0,0));
		}
	}
}