#include "Model.h"
#include <string>
#include <stdio.h>
#include <map>
#include <cstring>
#include "../Graphics.h"
#include "Resources.h"
#include "../../../../other/glm/gtc/matrix_transform.hpp"

void Model::render(){
	m_Graphics->PushMatrix();

	m_Graphics->SetModelMatrix(position,rot,vec3(1,1,1));
	m_Graphics->SetColor(coloring);

	//if(this!=m_Graphics->m_Resources->coordsModel)
	//m_Graphics->m_Resources->coordsModel->render();

	glBindTexture(GL_TEXTURE_2D,texture);
	glBindVertexArray(VAO);
	m_Graphics->SetLight(lighting);
	glDrawArrays(type , 0, vertex.size());
	m_Graphics->PopMatrix();
}

Model::Model(int type,Graphics* g,bool lighting){
	this->lighting=lighting;
	m_Graphics=g;
	this->type=type;
	position=vec3(0,0,0);
	rot=vec3(0,0,0);
	coloring=vec4(0,0,0,0);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1,&vbuffer);
	glGenBuffers(1,&nbuffer);
	glGenBuffers(1,&tbuffer);
	texture=g->m_Resources->textureBlank;
}
Model::Model(Graphics* g){
	lighting=false;
	m_Graphics=g;
	type=GL_TRIANGLES;
	position=vec3(0,0,0);
	rot=vec3(0,0,0);
	coloring=vec4(0,0,0,0);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1,&vbuffer);
	glGenBuffers(1,&nbuffer);
	glGenBuffers(1,&tbuffer);
	texture=g->m_Resources->textureBlank;
}
void Model::create(){
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER,vbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex.size()*3, &vertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(Graphics::SHADER_POS, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Graphics::SHADER_POS);

	glBindBuffer(GL_ARRAY_BUFFER,tbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texcoord.size()*2, &texcoord[0], GL_STATIC_DRAW);
	glVertexAttribPointer(Graphics::SHADER_TEXMAP, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Graphics::SHADER_TEXMAP);

	glBindBuffer(GL_ARRAY_BUFFER,nbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normal.size()*3, &normal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(Graphics::SHADER_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Graphics::SHADER_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER,0);
}

Model::~Model(){
	remove();
}

void Model::remove(){
	glDeleteBuffers(1,&vbuffer);
	glDeleteBuffers(1,&nbuffer);
	glDeleteBuffers(1,&tbuffer);
	glDeleteVertexArrays(1,&VAO);
	clear();
}

void Model::clear(){
	vertex.clear();
	normal.clear();
	texcoord.clear();
}

void Model::addVertex(vec3 v,vec3 n,vec2 t){
	vertex.push_back(v);
	normal.push_back(n);
	texcoord.push_back(t);
}

void Model::addVertex(std::vector<vec3> v,std::vector<vec3> n,std::vector<vec2> t){
	vertex.insert(vertex.end(),v.begin(),v.end());
	normal.insert(normal.end(),n.begin(),n.end());
	texcoord.insert(texcoord.end(),t.begin(),t.end());
}

void Model::addQuad(quad3 v,vec3 n,quad2 t){
			addVertex(v.p1,n,t.p10);
			addVertex(v.p2,n,t.p00);
			addVertex(v.p3,n,t.p01);

			addVertex(v.p1,n,t.p10);
			addVertex(v.p3,n,t.p01);
			addVertex(v.p4,n,t.p11);
}
