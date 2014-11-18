#include "Sphere.h"
#include "../Graphics.h"

Sphere::Sphere(Graphics* g,bool lighting, int rings, int sectors,vec3 lengthiness,float radius,quad2 texc,bool backstart):Model(GL_TRIANGLES,g,lighting){
	
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
				addVertex(vertices[ r * sectors + s+1],normals[ r * sectors + s+1],texcoords[ r * sectors + s+1]);

				addVertex(vertices[(r+1) * sectors + s+1],normals[(r+1) * sectors + s+1],texcoords[(r+1) * sectors + s+1]);

				addVertex(vertices[ (r+1) * sectors + (s)],normals[ (r+1) * sectors + (s)],texcoords[ (r+1) * sectors + (s)]);

				addVertex(vertices[ r * sectors + s+1],normals[ r * sectors + s+1],texcoords[ r * sectors + s+1]);

				addVertex(vertices[ (r+1) * sectors + (s)],normals[ (r+1) * sectors + (s)],texcoords[ (r+1) * sectors + (s)]);

				addVertex(vertices[ r * sectors + (s)],normals[ r * sectors + (s)],texcoords[ r * sectors + (s)]);
			}
		else
			for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
				addVertex(vertices[ r * sectors + s],normals[ r * sectors + s],texcoords[ r * sectors + s]);

				addVertex(vertices[(r+1) * sectors + s],normals[(r+1) * sectors + s],texcoords[(r+1) * sectors + s]);

				addVertex(vertices[ (r+1) * sectors + (s+1)],normals[ (r+1) * sectors + (s+1)],texcoords[ (r+1) * sectors + (s+1)]);

				addVertex(vertices[ r * sectors + s],normals[ r * sectors + s],texcoords[ r * sectors + s]);

				addVertex(vertices[ (r+1) * sectors + (s+1)],normals[ (r+1) * sectors + (s+1)],texcoords[ (r+1) * sectors + (s+1)]);

				addVertex(vertices[ r * sectors + (s+1)],normals[ r * sectors + (s+1)],texcoords[ r * sectors + (s+1)]);
			}
}