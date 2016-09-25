#include "ObjModel.h"
#include <fstream>
#include <shared/System.h>
#include <sstream>

Geometry3d ObjModel(const std::string &filename, const glm::vec3 &position) {
	Geometry3d geom;
	std::ifstream file(g_System()->GetDataFile(filename + ".model"));
	if (!file.good()) {
		file.close();
		return geom;
	}
	std::string line;
	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> norms;
	std::vector<glm::vec2> texs;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string com;
		if (!(iss >> com)) {
			continue;
		}
		if (com == "v") {
			glm::vec3 v;
			if (!(iss >> v.x >> v.y >> v.z)) {
				continue;
			}
			glm::vec3 buf = v;
			buf *= 32;
			buf += position;
			verts.push_back(buf);
		} else if (com == "vn") {
			glm::vec3 vn;
			if (!(iss >> vn.x >> vn.y >> vn.z)) {
				continue;
			}
			norms.push_back(vn);
		} else if (com == "vt") {
			glm::vec2 vt;
			if (!(iss >> vt.x >> vt.y)) {
				continue;
			}
			vt.y = 1 - vt.y;
			texs.push_back(vt);
		} else if (com == "f") {
			if (!norms.empty() && !texs.empty()) {
				int v1, v2, v3, t1, t2, t3, n1, n2, n3;
				char c;
				if (!(iss >> v1 >> c >> t1 >> c >> n1 >> v2 >> c >> t2 >> c >> n2 >> v3 >>
				      c >> t3 >> c >> n3)) {
					continue;
				}
				geom.Push(verts[v1 - 1], norms[n1 - 1], texs[t1 - 1]);
				geom.Push(verts[v2 - 1], norms[n2 - 1], texs[t2 - 1]);
				geom.Push(verts[v3 - 1], norms[n3 - 1], texs[t3 - 1]);
			} else if (!norms.empty()) {
				int v1, v2, v3, n1, n2, n3;
				char c;
				if (!(iss >> v1 >> c >> c >> n1 >> v2 >> c >> c >> n2 >> v3 >> c >> c >>
				      n3)) {
					continue;
				}
				geom.Push(verts[v1 - 1], norms[n1 - 1], glm::vec2(0, 0));
				geom.Push(verts[v2 - 1], norms[n2 - 1], glm::vec2(0, 0));
				geom.Push(verts[v3 - 1], norms[n3 - 1], glm::vec2(0, 0));
			} else if (!texs.empty()) {
				int v1, v2, v3, t1, t2, t3;
				char c;
				if (!(iss >> v1 >> c >> t1 >> c >> v2 >> c >> t2 >> c >> v3 >> c >> t3)) {
					continue;
				}
				geom.Push(verts[v1 - 1], glm::vec3(0, 0, 1), texs[t1 - 1]);
				geom.Push(verts[v2 - 1], glm::vec3(0, 0, 1), texs[t2 - 1]);
				geom.Push(verts[v3 - 1], glm::vec3(0, 0, 1), texs[t3 - 1]);
			} else {
				int v1, v2, v3;
				if (!(iss >> v1 >> v2 >> v3)) {
					continue;
				}
				geom.Push(verts[v1 - 1], glm::vec3(0, 0, 1), glm::vec2(0, 0));
				geom.Push(verts[v2 - 1], glm::vec3(0, 0, 1), glm::vec2(0, 0));
				geom.Push(verts[v3 - 1], glm::vec3(0, 0, 1), glm::vec2(0, 0));
			}
		}
	}
	file.close();
	return geom;
}
