#include "Model.h"
#include <string>
#include <cstdio>
#include <map>
#include <cstring>
#include <fstream>
#include <sstream>
#include "../Resources.h"
#include "../Texture.h"
#include "../../Graphics.h"
#include "../../../Client.h"
#include "../../../../shared/System.h"
	
void Model::Render(const glm::mat4 &parentMatrix){
	if(!g_Graphics()->restoreMatrix)
		modelMatrix=parentMatrix;

	g_Graphics()->SetModelMatrix(modelMatrix,normalMatrix,position,rotation,scale);
	g_Graphics()->SetColor(color);

	//if(this!=g_Graphics()->m_Resources->coordsModel)
	//g_Graphics()->m_Resources->coordsModel->render(modelMatrix);

	texture->Bind();
	glBindVertexArray(vao);
	g_Graphics()->SetLight(lighting);
	glDrawArrays(type , 0, vertex.size());
}

Model::Model(bool lighting, int type){
	this->lighting=lighting;
	this->type=type;
	position=vec3(0,0,0);
	rotation=vec3(0,0,0);
	color=vec4(1,1,1,0);
	scale=vec3(1,1,1);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1,&vbuffer);
	glGenBuffers(1,&nbuffer);
	glGenBuffers(1,&tbuffer);
	texture = g_Graphics()->m_Resources->textureBlank;
}
void Model::Create(){
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER,vbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex.size()*3, vertex.size()>0 ? &vertex[0] : NULL, GL_STATIC_DRAW);
	glVertexAttribPointer(Graphics::SHADER_POS, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Graphics::SHADER_POS);

	glBindBuffer(GL_ARRAY_BUFFER,tbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texcoord.size()*2, texcoord.size()>0 ? &texcoord[0] : NULL, GL_STATIC_DRAW);
	glVertexAttribPointer(Graphics::SHADER_TEXMAP, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Graphics::SHADER_TEXMAP);

	glBindBuffer(GL_ARRAY_BUFFER,nbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normal.size()*3, normal.size()>0 ? &normal[0] : NULL, GL_STATIC_DRAW);
	glVertexAttribPointer(Graphics::SHADER_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Graphics::SHADER_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER,0);
}

Model::~Model(){
	glDeleteBuffers(1, &vbuffer);
	glDeleteBuffers(1, &nbuffer);
	glDeleteBuffers(1, &tbuffer);
	glDeleteVertexArrays(1, &vao);
	Clear();
}

void Model::Clear(){
	vertex.clear();
	normal.clear();
	texcoord.clear();
}

void Model::AddVertex(vec3 v,vec3 n,vec2 t){
	vertex.push_back(v);
	normal.push_back(n);
	texcoord.push_back(t);
}

void Model::AddVertex(std::vector<vec3> v,std::vector<vec3> n,std::vector<vec2> t){
	vertex.insert(vertex.end(),v.begin(),v.end());
	normal.insert(normal.end(),n.begin(),n.end());
	texcoord.insert(texcoord.end(),t.begin(),t.end());
}

void Model::AddQuad(quad3 v,vec3 n,quad2 t){
	AddVertex(v.p1,n,t.p10);
	AddVertex(v.p2,n,t.p00);
	AddVertex(v.p3,n,t.p01);

	AddVertex(v.p1,n,t.p10);
	AddVertex(v.p3,n,t.p01);
	AddVertex(v.p4,n,t.p11);
}

void Model::AddSphere(int rings, int sectors,vec3 lengthiness,float radius,quad2 texc,bool backstart){

	float const R = 1./(float)(rings-1);
	float const S = 1./(float)(sectors-1);
	int r, s;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec2> texcoords;

	vertices.resize(rings * sectors);
	normals.resize(rings * sectors);
	texcoords.resize(rings * sectors);
	std::vector<vec3>::iterator v = vertices.begin();
	std::vector<vec3>::iterator n = normals.begin();
	std::vector<vec2>::iterator t = texcoords.begin();
	float tcsizex=texc.p10.x-texc.p00.x;
	float tcsizey=texc.p01.y-texc.p00.y;
	if(backstart)
		for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
			float const z = -sin( -M_PI_2 + M_PI * r * R );
			float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
			float const y = sin(2*M_PI * s * S) * sin( M_PI * r * R );
			*t++ = vec2(texc.p00.x+s*S*tcsizex,texc.p00.y+r*R*tcsizey);
			*v++ = vec3(-x * radius*lengthiness.x,y * radius*lengthiness.y,z*radius*lengthiness.z);
			*n++ = vec3(-x,y,z);
		}
	else
		for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
			float const z = -sin( -M_PI_2 + M_PI * r * R );
			float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
			float const y = sin(2*M_PI * s * S) * sin( M_PI * r * R );
			*t++ = vec2(texc.p00.x+s*S*tcsizex,texc.p00.y+r*R*tcsizey);
			*v++ = vec3(x * radius*lengthiness.x,y * radius*lengthiness.y,z*radius*lengthiness.z);
			*n++ = vec3(x,y,z);
		}
		if(backstart)
			for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
				AddVertex(vertices[ r * sectors + s+1],normals[ r * sectors + s+1],texcoords[ r * sectors + s+1]);

				AddVertex(vertices[(r+1) * sectors + s+1],normals[(r+1) * sectors + s+1],texcoords[(r+1) * sectors + s+1]);

				AddVertex(vertices[ (r+1) * sectors + (s)],normals[ (r+1) * sectors + (s)],texcoords[ (r+1) * sectors + (s)]);

				AddVertex(vertices[ r * sectors + s+1],normals[ r * sectors + s+1],texcoords[ r * sectors + s+1]);

				AddVertex(vertices[ (r+1) * sectors + (s)],normals[ (r+1) * sectors + (s)],texcoords[ (r+1) * sectors + (s)]);

				AddVertex(vertices[ r * sectors + (s)],normals[ r * sectors + (s)],texcoords[ r * sectors + (s)]);
			}
		else
			for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
				AddVertex(vertices[ r * sectors + s],normals[ r * sectors + s],texcoords[ r * sectors + s]);

				AddVertex(vertices[(r+1) * sectors + s],normals[(r+1) * sectors + s],texcoords[(r+1) * sectors + s]);

				AddVertex(vertices[ (r+1) * sectors + (s+1)],normals[ (r+1) * sectors + (s+1)],texcoords[ (r+1) * sectors + (s+1)]);

				AddVertex(vertices[ r * sectors + s],normals[ r * sectors + s],texcoords[ r * sectors + s]);

				AddVertex(vertices[ (r+1) * sectors + (s+1)],normals[ (r+1) * sectors + (s+1)],texcoords[ (r+1) * sectors + (s+1)]);

				AddVertex(vertices[ r * sectors + (s+1)],normals[ r * sectors + (s+1)],texcoords[ r * sectors + (s+1)]);
			}
}

void Model::AddObjModel(string filename){
	std::ifstream file(g_System()->GetDataFile(filename));
	if(!file.good()) {
		file.close();
		return;
	}
	std::string line;
	std::vector <vec3> verts;
	std::vector <vec3> norms;
	std::vector <vec2> texs;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string com;
		if (!(iss >> com)) { continue; }
		if(com.compare("v")==0){
			vec3 v;
			if (!(iss >> v.x>>v.y>>v.z)) { continue; }
			vec3 buf=v;
			buf*=32;
			verts.push_back(buf);
		}
		else if(com.compare("vn")==0){
			vec3 vn;
			if (!(iss >> vn.x>>vn.y>>vn.z)) { continue; }
			norms.push_back(vn);
		}
		else if(com.compare("vt")==0){
			vec2 vt;
			if (!(iss >> vt.x>>vt.y)) { continue; }
			vt.y=1-vt.y;
			texs.push_back(vt);
		}
		else if(com.compare("f")==0){
			if(norms.size()>0 && texs.size()>0){
				int v1,v2,v3,t1,t2,t3,n1,n2,n3;
				char c;
				if (!(iss >>v1>>c>>t1>>c>>n1>>v2>>c>>t2>>c>>n2>>v3>>c>>t3>>c>>n3)) { continue; }
				AddVertex(verts[v1-1],norms[n1-1],texs[t1-1]);
				AddVertex(verts[v2-1],norms[n2-1],texs[t2-1]);
				AddVertex(verts[v3-1],norms[n3-1],texs[t3-1]);
			}
			else if(norms.size()>0){
				int v1,v2,v3,n1,n2,n3;
				char c;
				if (!(iss >>v1>>c>>c>>n1>>v2>>c>>c>>n2>>v3>>c>>c>>n3)) { continue; }
				AddVertex(verts[v1-1],norms[n1-1],vec2(0,0));
				AddVertex(verts[v2-1],norms[n2-1],vec2(0,0));
				AddVertex(verts[v3-1],norms[n3-1],vec2(0,0));
			}
			else if(texs.size()>0){
				int v1,v2,v3,t1,t2,t3;
				char c;
				if (!(iss >>v1>>c>>t1>>c>>v2>>c>>t2>>c>>v3>>c>>t3)) { continue; }
				AddVertex(verts[v1-1],vec3(0,0,1),texs[t1-1]);
				AddVertex(verts[v2-1],vec3(0,0,1),texs[t2-1]);
				AddVertex(verts[v3-1],vec3(0,0,1),texs[t3-1]);
			}
			else{
				int v1,v2,v3;
				if (!(iss >>v1>>v2>>v3)) { continue; }
				AddVertex(verts[v1-1],vec3(0,0,1),vec2(0,0));
				AddVertex(verts[v2-1],vec3(0,0,1),vec2(0,0));
				AddVertex(verts[v3-1],vec3(0,0,1),vec2(0,0));
			}
		}
	}
	file.close();
}
void Model::AddRectangle(quad2 in, quad2 out, float depth){
	quad2 tex(0,0,1,1);
	vec3 n=vec3(0,1,0);
	AddQuad(quad3(in, depth), n, tex);
	float roundedleft=(in.p00-out.p00).x;
	float roundedbottom=(in.p00-out.p00).y;
	float roundedright=(out.p11-in.p11).x;
	float roundedtop=(out.p11-in.p11).y;
	AddQuad(quad3(quad2(in.p01, in.p11, out.p01 + vec2(roundedleft, 0), out.p11 - vec2(roundedright, 0)), depth), n, tex);
	AddQuad(quad3(quad2(out.p00 + vec2(roundedleft, 0), out.p10 - vec2(roundedright, 0), in.p00, in.p10), depth), n, tex);
	AddQuad(quad3(quad2(out.p00 + vec2(0, roundedbottom), in.p00, out.p01 - vec2(0, roundedtop), in.p01), depth), n, tex);
	AddQuad(quad3(quad2(in.p10, out.p10 + vec2(0, roundedbottom), in.p11, out.p11 - vec2(0, roundedtop)), depth), n, tex);

	if(glm::min(roundedright,roundedtop)!=0){
		int quality=g_Graphics()->to_pixels(glm::max(roundedright,roundedtop))/4;

		for(int i=0;i<quality;i++){
			AddVertex(quad2::vec2vec3(in.p11 + vec2(cos((i + 1)*M_PI_2 / quality)*roundedright, sin((i + 1)*M_PI_2 / quality)*roundedtop), depth), n, vec2(0, 0));
			AddVertex(quad2::vec2vec3(in.p11, depth), n, vec2(0, 0));
			AddVertex(quad2::vec2vec3(in.p11 + vec2(cos(i*M_PI_2 / quality)*roundedright, sin(i*M_PI_2 / quality)*roundedtop), depth), n, vec2(0, 0));
		}
	}
	if(glm::min(roundedright,roundedbottom)!=0){
		int quality=g_Graphics()->to_pixels(glm::max(roundedright,roundedbottom))/4;
		for(int i=0;i<quality;i++){
			AddVertex(quad2::vec2vec3(in.p10 + vec2(cos(i*M_PI_2 / quality)*roundedright, -sin(i*M_PI_2 / quality)*roundedbottom), depth), n, vec2(0, 0));
			AddVertex(quad2::vec2vec3(in.p10, depth), n, vec2(0, 0));
			AddVertex(quad2::vec2vec3(in.p10 + vec2(cos((i + 1)*M_PI_2 / quality)*roundedright, -sin((i + 1)*M_PI_2 / quality)*roundedbottom), depth), n, vec2(0, 0));
		}
	}
	if(glm::min(roundedleft,roundedbottom)!=0){
		int quality=g_Graphics()->to_pixels(glm::max(roundedleft,roundedbottom))/4;
		for(int i=0;i<quality;i++){
			AddVertex(quad2::vec2vec3(in.p00 + vec2(-cos((i + 1)*M_PI_2 / quality)*roundedleft, -sin((i + 1)*M_PI_2 / quality)*roundedbottom), depth), n, vec2(0, 0));
			AddVertex(quad2::vec2vec3(in.p00, depth), n, vec2(0, 0));
			AddVertex(quad2::vec2vec3(in.p00 + vec2(-cos(i*M_PI_2 / quality)*roundedleft, -sin(i*M_PI_2 / quality)*roundedbottom), depth), n, vec2(0, 0));
		}
	}
	if(glm::min(roundedleft,roundedtop)!=0){
		int quality=g_Graphics()->to_pixels(glm::max(roundedleft,roundedtop))/4;
		for(int i=0;i<quality;i++){
			AddVertex(quad2::vec2vec3(in.p01 + vec2(-cos(i*M_PI_2 / quality)*roundedleft, sin(i*M_PI_2 / quality)*roundedtop), depth), n, vec2(0, 0));
			AddVertex(quad2::vec2vec3(in.p01, depth), n, vec2(0, 0));
			AddVertex(quad2::vec2vec3(in.p01 + vec2(-cos((i + 1)*M_PI_2 / quality)*roundedleft, sin((i + 1)*M_PI_2 / quality)*roundedtop), depth), n, vec2(0, 0));
		}
	}
}

void Model::LookAt(vec3 to){
	rotation=quad2::vec2rot(normalize(to-position));
}
void Model::ScaleAt(vec3 to,vec3 basic, vec3 additional){
	scale=additional*length(to-position)+basic;
}