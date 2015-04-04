#include "Model2d.h"
#include <string>
#include <stdio.h>
#include <map>
#include <cstring>
#include "../../Client.h"
#include "../Graphics.h"
#include "Resources.h"

void Model2d::render(){
	Client::m_Graphics()->SetPos2d(position, depth);
	Client::m_Graphics()->SetColor2d(coloring);

	glBindTexture(GL_TEXTURE_2D,texture);
	glBindVertexArray(VAO);
	glDrawArrays(type , 0, vertex.size());
}
Model2d::Model2d(int type){
	this->type=type;
	position=vec2(0,0);
	coloring=vec4(0,0,0,0);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1,&vbuffer);
	glGenBuffers(1,&tbuffer);
	texture = Client::m_Graphics()->m_Resources->textureBlank;
	depth = 0;
}
Model2d::Model2d(){
	type=GL_TRIANGLES;
	position=vec2(0,0);
	coloring=vec4(0,0,0,0);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1,&vbuffer);
	glGenBuffers(1,&tbuffer);
	texture = Client::m_Graphics()->m_Resources->textureBlank;
	depth = 0;
}
void Model2d::create(){
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER,vbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex.size()*2, &vertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(Graphics::SHADER_POS, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Graphics::SHADER_POS);

	glBindBuffer(GL_ARRAY_BUFFER,tbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texcoord.size()*2, &texcoord[0], GL_STATIC_DRAW);
	glVertexAttribPointer(Graphics::SHADER_TEXMAP, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Graphics::SHADER_TEXMAP);

	glBindBuffer(GL_ARRAY_BUFFER,0);
}
Model2d::~Model2d(){
	remove();
}
void Model2d::remove(){
	glDeleteBuffers(1,&vbuffer);
	glDeleteBuffers(1,&tbuffer);
	glDeleteVertexArrays(1,&VAO);
	clear();
}
void Model2d::clear(){
	vertex.clear();
	texcoord.clear();
}
void Model2d::addVertex(vec2 v,vec2 t){
	vertex.push_back(v);
	texcoord.push_back(t);
}
void Model2d::addVertex(std::vector<vec2> v,std::vector<vec2> t){
	vertex.insert(vertex.end(),v.begin(),v.end());
	texcoord.insert(texcoord.end(),t.begin(),t.end());
}
void Model2d::addQuad(quad2 v,quad2 t){
			addVertex(v.p00,t.p00);
			addVertex(v.p10,t.p10);
			addVertex(v.p01,t.p01);

			addVertex(v.p01,t.p01);
			addVertex(v.p10,t.p10);
			addVertex(v.p11,t.p11);
}

void Model2d::addRectangle(quad2 in,quad2 out){
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
		int quality=Client::m_Graphics()->to_pixels(glm::max(roundedright,roundedtop))/4;

		for(int i=0;i<quality;i++){
			addVertex(in.p11,vec2(0,0));
			addVertex(in.p11+vec2(cos(i*M_PI_2/quality)*roundedright,sin(i*M_PI_2/quality)*roundedtop),vec2(0,0));
			addVertex(in.p11+vec2(cos((i+1)*M_PI_2/quality)*roundedright,sin((i+1)*M_PI_2/quality)*roundedtop),vec2(0,0));
		}
	}
	if(glm::min(roundedright,roundedbottom)!=0){
		int quality=Client::m_Graphics()->to_pixels(glm::max(roundedright,roundedbottom))/4;
		for(int i=0;i<quality;i++){
			addVertex(in.p10+vec2(cos(i*M_PI_2/quality)*roundedright,-sin(i*M_PI_2/quality)*roundedbottom),vec2(0,0));
			addVertex(in.p10,vec2(0,0));
			addVertex(in.p10+vec2(cos((i+1)*M_PI_2/quality)*roundedright,-sin((i+1)*M_PI_2/quality)*roundedbottom),vec2(0,0));
		}
	}
	if(glm::min(roundedleft,roundedbottom)!=0){
		int quality=Client::m_Graphics()->to_pixels(glm::max(roundedleft,roundedbottom))/4;
		for(int i=0;i<quality;i++){
			addVertex(in.p00,vec2(0,0));
			addVertex(in.p00+vec2(-cos(i*M_PI_2/quality)*roundedleft,-sin(i*M_PI_2/quality)*roundedbottom),vec2(0,0));
			addVertex(in.p00+vec2(-cos((i+1)*M_PI_2/quality)*roundedleft,-sin((i+1)*M_PI_2/quality)*roundedbottom),vec2(0,0));
		}
	}
	if(glm::min(roundedleft,roundedtop)!=0){
		int quality=Client::m_Graphics()->to_pixels(glm::max(roundedleft,roundedtop))/4;
		for(int i=0;i<quality;i++){
			addVertex(in.p01+vec2(-cos(i*M_PI_2/quality)*roundedleft,sin(i*M_PI_2/quality)*roundedtop),vec2(0,0));
			addVertex(in.p01,vec2(0,0));
			addVertex(in.p01+vec2(-cos((i+1)*M_PI_2/quality)*roundedleft,sin((i+1)*M_PI_2/quality)*roundedtop),vec2(0,0));
		}
	}
}