#include "Sphere.h"

Sphere::Sphere() {
	radius = 1.0f;
	position = glm::vec3(0, 0, 0);
	texcoord = quad2(0, 0, 1, 1);
	rings = 32;
	sectors = 32;
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	reversed = false;
}
Sphere &Sphere::SetRadius(float radius) {
	this->radius = radius;
	return *this;
}
Sphere &Sphere::SetPosition(const glm::vec3 &position) {
	this->position = position;
	return *this;
}
Sphere &Sphere::SetTexCoord(const quad2 &texcoord) {
	this->texcoord = texcoord;
	return *this;
}
Sphere &Sphere::SetRings(int rings) {
	this->rings = rings;
	return *this;
}
Sphere &Sphere::SetSectors(int sectors) {
	this->sectors = sectors;
	return *this;
}
Sphere &Sphere::SetScale(const glm::vec3 &scale) {
	this->scale = scale;
	return *this;
}
Sphere &Sphere::SetReversed(bool reversed) {
	this->reversed = reversed;
	return *this;
}
Sphere::operator Geometry3d() {
	Geometry3d g;
	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int r, s;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;

	vertices.resize(rings * sectors);
	normals.resize(rings * sectors);
	texcoords.resize(rings * sectors);
	std::vector<glm::vec3>::iterator v = vertices.begin();
	std::vector<glm::vec3>::iterator n = normals.begin();
	std::vector<glm::vec2>::iterator t = texcoords.begin();
	float tcsizex = texcoord.p10.x - texcoord.p00.x;
	float tcsizey = texcoord.p01.y - texcoord.p00.y;
	if (reversed)
		for (r = 0; r < rings; r++)
			for (s = 0; s < sectors; s++) {
				float const z = -sin(-M_PI_2 + M_PI * r * R);
				float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
				float const y = sin(2 * M_PI * s * S) * sin(M_PI * r * R);
				*t++ = glm::vec2(texcoord.p00.x + s * S * tcsizex,
				                 texcoord.p00.y + r * R * tcsizey);
				*v++ = glm::vec3(-x * radius * scale.x, y * radius * scale.y,
				                 z * radius * scale.z) +
				       position;
				*n++ = glm::vec3(-x, y, z);
			}
	else
		for (r = 0; r < rings; r++)
			for (s = 0; s < sectors; s++) {
				float const z = -sin(-M_PI_2 + M_PI * r * R);
				float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
				float const y = sin(2 * M_PI * s * S) * sin(M_PI * r * R);
				*t++ = glm::vec2(texcoord.p00.x + s * S * tcsizex,
				                 texcoord.p00.y + r * R * tcsizey);
				*v++ = glm::vec3(x * radius * scale.x, y * radius * scale.y,
				                 z * radius * scale.z) +
				       position;
				*n++ = glm::vec3(x, y, z);
			}

	if (reversed)
		for (r = 0; r < rings - 1; r++)
			for (s = 0; s < sectors - 1; s++) {
				g.Push(vertices[r * sectors + s + 1], normals[r * sectors + s + 1],
				       texcoords[r * sectors + s + 1]);
				g.Push(vertices[(r + 1) * sectors + s + 1],
				       normals[(r + 1) * sectors + s + 1],
				       texcoords[(r + 1) * sectors + s + 1]);
				g.Push(vertices[(r + 1) * sectors + (s)], normals[(r + 1) * sectors + (s)],
				       texcoords[(r + 1) * sectors + (s)]);
				g.Push(vertices[r * sectors + s + 1], normals[r * sectors + s + 1],
				       texcoords[r * sectors + s + 1]);
				g.Push(vertices[(r + 1) * sectors + (s)], normals[(r + 1) * sectors + (s)],
				       texcoords[(r + 1) * sectors + (s)]);
				g.Push(vertices[r * sectors + (s)], normals[r * sectors + (s)],
				       texcoords[r * sectors + (s)]);
			}
	else
		for (r = 0; r < rings - 1; r++)
			for (s = 0; s < sectors - 1; s++) {
				g.Push(vertices[r * sectors + s], normals[r * sectors + s],
				       texcoords[r * sectors + s]);
				g.Push(vertices[(r + 1) * sectors + s], normals[(r + 1) * sectors + s],
				       texcoords[(r + 1) * sectors + s]);
				g.Push(vertices[(r + 1) * sectors + (s + 1)],
				       normals[(r + 1) * sectors + (s + 1)],
				       texcoords[(r + 1) * sectors + (s + 1)]);
				g.Push(vertices[r * sectors + s], normals[r * sectors + s],
				       texcoords[r * sectors + s]);
				g.Push(vertices[(r + 1) * sectors + (s + 1)],
				       normals[(r + 1) * sectors + (s + 1)],
				       texcoords[(r + 1) * sectors + (s + 1)]);
				g.Push(vertices[r * sectors + (s + 1)], normals[r * sectors + (s + 1)],
				       texcoords[r * sectors + (s + 1)]);
			}
	return g;
}