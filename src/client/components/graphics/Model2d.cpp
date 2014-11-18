#include "Model2d.h"
#include <string>
#include <stdio.h>
#include <map>
#include <cstring>
#include "../Graphics.h"
#include "Resources.h"

void Model2d::render(){
	m_Graphics->SetPos2d(position);
	m_Graphics->SetColor2d(coloring);

	glBindTexture(GL_TEXTURE_2D,texture);
	glBindVertexArray(VAO);
	glDrawArrays(type , 0, vertex.size());
}
Model2d::Model2d(int type,Graphics* g){
	m_Graphics=g;
	this->type=type;
	position=vec2(0,0);
	coloring=vec4(0,0,0,0);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1,&vbuffer);
	glGenBuffers(1,&tbuffer);
	texture=g->m_Resources->textureBlank;
}
Model2d::Model2d(Graphics* g){
	m_Graphics=g;
	type=GL_TRIANGLES;
	position=vec2(0,0);
	coloring=vec4(0,0,0,0);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1,&vbuffer);
	glGenBuffers(1,&tbuffer);
	texture=g->m_Resources->textureBlank;
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
			addVertex(v.p10,t.p10);
			addVertex(v.p00,t.p00);
			addVertex(v.p01,t.p01);

			addVertex(v.p10,t.p10);
			addVertex(v.p01,t.p01);
			addVertex(v.p11,t.p11);
}
