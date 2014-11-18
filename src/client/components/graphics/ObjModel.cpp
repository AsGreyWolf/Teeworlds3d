#include "ObjModel.h"
#include <fstream>
#include <sstream>
#include <cstring>
#include <map>
#include "../../Client.h"
#include "../Graphics.h"

ObjModel::ObjModel(Graphics* g,bool lighting,string filename):Model(GL_TRIANGLES,g,lighting){
	std::ifstream file(m_Graphics->m_Client->GetDataFile(filename));
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
				addVertex(verts[v1-1],norms[n1-1],texs[t1-1]);
				addVertex(verts[v2-1],norms[n2-1],texs[t2-1]);
				addVertex(verts[v3-1],norms[n3-1],texs[t3-1]);
			}
			else if(norms.size()>0){
				int v1,v2,v3,n1,n2,n3;
				char c;
				if (!(iss >>v1>>c>>c>>n1>>v2>>c>>c>>n2>>v3>>c>>c>>n3)) { continue; }
				addVertex(verts[v1-1],norms[n1-1],vec2(0,0));
				addVertex(verts[v2-1],norms[n2-1],vec2(0,0));
				addVertex(verts[v3-1],norms[n3-1],vec2(0,0));
			}
			else if(texs.size()>0){
				int v1,v2,v3,t1,t2,t3;
				char c;
				if (!(iss >>v1>>c>>t1>>c>>v2>>c>>t2>>c>>v3>>c>>t3)) { continue; }
				addVertex(verts[v1-1],vec3(0,0,1),texs[t1-1]);
				addVertex(verts[v2-1],vec3(0,0,1),texs[t2-1]);
				addVertex(verts[v3-1],vec3(0,0,1),texs[t3-1]);
			}
			else{
				int v1,v2,v3;
				if (!(iss >>v1>>v2>>v3)) { continue; }
				addVertex(verts[v1-1],vec3(0,0,1),vec2(0,0));
				addVertex(verts[v2-1],vec3(0,0,1),vec2(0,0));
				addVertex(verts[v3-1],vec3(0,0,1),vec2(0,0));
			}
		}
	}
	file.close();
}
