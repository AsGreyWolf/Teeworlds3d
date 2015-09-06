#include "Model2d.h"
#include <string>
#include <stdio.h>
#include <map>
#include <cstring>
#include "../../Client.h"
#include "../Graphics.h"
#include "Resources.h"

void Model2d::Render(){
	g_Graphics()->SetPos2d(position, depth);
	g_Graphics()->SetColor2d(coloring);

	glBindTexture(GL_TEXTURE_2D,texture);
	glBindVertexArray(vao);
	glDrawArrays(type , 0, vertex.size());
}
Model2d::Model2d(int type){
	this->type=type;
	position=vec2(0,0);
	coloring=vec4(0,0,0,0);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1,&vbuffer);
	glGenBuffers(1,&tbuffer);
	texture = g_Graphics()->m_Resources->textureBlank;
	depth = 0;
}
Model2d::Model2d():Model2d(GL_TRIANGLES) {}
void Model2d::Create(){
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER,vbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex.size()*2, vertex.size()>0?&vertex[0]:NULL, GL_STATIC_DRAW);
	glVertexAttribPointer(Graphics::SHADER_POS, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Graphics::SHADER_POS);

	glBindBuffer(GL_ARRAY_BUFFER,tbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texcoord.size()*2, vertex.size()>0 ? &texcoord[0] : NULL, GL_STATIC_DRAW);
	glVertexAttribPointer(Graphics::SHADER_TEXMAP, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Graphics::SHADER_TEXMAP);

	glBindBuffer(GL_ARRAY_BUFFER,0);
}
Model2d::~Model2d(){
	Remove();
}
void Model2d::Remove(){
	glDeleteBuffers(1,&vbuffer);
	glDeleteBuffers(1,&tbuffer);
	glDeleteVertexArrays(1,&vao);
	Clear();
}
void Model2d::Clear(){
	vertex.clear();
	texcoord.clear();
}
void Model2d::AddVertex(vec2 v,vec2 t){
	vertex.push_back(v);
	texcoord.push_back(t);
}
void Model2d::AddVertex(std::vector<vec2> v,std::vector<vec2> t){
	vertex.insert(vertex.end(),v.begin(),v.end());
	texcoord.insert(texcoord.end(),t.begin(),t.end());
}
void Model2d::AddQuad(quad2 v,quad2 t){
			AddVertex(v.p00,t.p00);
			AddVertex(v.p10,t.p10);
			AddVertex(v.p01,t.p01);

			AddVertex(v.p01,t.p01);
			AddVertex(v.p10,t.p10);
			AddVertex(v.p11,t.p11);
}

void Model2d::AddRectangle(quad2 in,quad2 out){
	quad2 tex(0,0,1,1);
	AddQuad(in,tex);
	float roundedleft=(in.p00-out.p00).x;
	float roundedbottom=(in.p00-out.p00).y;
	float roundedright=(out.p11-in.p11).x;
	float roundedtop=(out.p11-in.p11).y;
	AddQuad(quad2(in.p01,in.p11,out.p01+vec2(roundedleft,0),out.p11-vec2(roundedright,0)),tex);
	AddQuad(quad2(out.p00+vec2(roundedleft,0),out.p10-vec2(roundedright,0),in.p00,in.p10),tex);
	AddQuad(quad2(out.p00+vec2(0,roundedbottom),in.p00,out.p01-vec2(0,roundedtop),in.p01),tex);
	AddQuad(quad2(in.p10,out.p10+vec2(0,roundedbottom),in.p11,out.p11-vec2(0,roundedtop)),tex);

	if(glm::min(roundedright,roundedtop)!=0){
		int quality=g_Graphics()->to_pixels(glm::max(roundedright,roundedtop))/4;

		for(int i=0;i<quality;i++){
			AddVertex(in.p11,vec2(0,0));
			AddVertex(in.p11+vec2(cos(i*M_PI_2/quality)*roundedright,sin(i*M_PI_2/quality)*roundedtop),vec2(0,0));
			AddVertex(in.p11+vec2(cos((i+1)*M_PI_2/quality)*roundedright,sin((i+1)*M_PI_2/quality)*roundedtop),vec2(0,0));
		}
	}
	if(glm::min(roundedright,roundedbottom)!=0){
		int quality=g_Graphics()->to_pixels(glm::max(roundedright,roundedbottom))/4;
		for(int i=0;i<quality;i++){
			AddVertex(in.p10+vec2(cos(i*M_PI_2/quality)*roundedright,-sin(i*M_PI_2/quality)*roundedbottom),vec2(0,0));
			AddVertex(in.p10,vec2(0,0));
			AddVertex(in.p10+vec2(cos((i+1)*M_PI_2/quality)*roundedright,-sin((i+1)*M_PI_2/quality)*roundedbottom),vec2(0,0));
		}
	}
	if(glm::min(roundedleft,roundedbottom)!=0){
		int quality=g_Graphics()->to_pixels(glm::max(roundedleft,roundedbottom))/4;
		for(int i=0;i<quality;i++){
			AddVertex(in.p00,vec2(0,0));
			AddVertex(in.p00+vec2(-cos(i*M_PI_2/quality)*roundedleft,-sin(i*M_PI_2/quality)*roundedbottom),vec2(0,0));
			AddVertex(in.p00+vec2(-cos((i+1)*M_PI_2/quality)*roundedleft,-sin((i+1)*M_PI_2/quality)*roundedbottom),vec2(0,0));
		}
	}
	if(glm::min(roundedleft,roundedtop)!=0){
		int quality=g_Graphics()->to_pixels(glm::max(roundedleft,roundedtop))/4;
		for(int i=0;i<quality;i++){
			AddVertex(in.p01+vec2(-cos(i*M_PI_2/quality)*roundedleft,sin(i*M_PI_2/quality)*roundedtop),vec2(0,0));
			AddVertex(in.p01,vec2(0,0));
			AddVertex(in.p01+vec2(-cos((i+1)*M_PI_2/quality)*roundedleft,sin((i+1)*M_PI_2/quality)*roundedtop),vec2(0,0));
		}
	}
}