#include "Primitives.h"

Geometry3d Point(const glm::vec3 &v, const glm::vec3 &n, const glm::vec2 &t) {
	Geometry3d geom;
	geom.Push(v, n, t);
	return geom;
}
Geometry3d Line(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &n1,
                const glm::vec3 &n2, const glm::vec2 &t1, const glm::vec2 &t2) {
	Geometry3d geom;
	geom.Push(v1, n1, t1);
	geom.Push(v2, n2, t2);
	return geom;
}
Geometry3d Quad(const quad3 &v, const glm::vec3 &n, const quad2 &t) {
	Geometry3d geom;
	geom.Push(v.p1, n, t.v10());
	geom.Push(v.p2, n, t.v00());
	geom.Push(v.p3, n, t.v01());

	geom.Push(v.p1, n, t.v10());
	geom.Push(v.p3, n, t.v01());
	geom.Push(v.p4, n, t.v11());
	return geom;
}

Geometry2d Point(const glm::vec2 &v, const glm::vec2 &t) {
	Geometry2d geom;
	geom.Push(v, t);
	return geom;
}
Geometry2d Line(const glm::vec2 &v1, const glm::vec2 &v2, const glm::vec2 &t1,
                const glm::vec2 &t2) {
	Geometry2d geom;
	geom.Push(v1, t1);
	geom.Push(v2, t2);
	return geom;
}
Geometry2d Quad(const quad2 &v, const quad2 &t) {
	Geometry2d geom;
	geom.Push(v.v00(), t.v00());
	geom.Push(v.v10(), t.v10());
	geom.Push(v.v01(), t.v01());

	geom.Push(v.v01(), t.v01());
	geom.Push(v.v10(), t.v10());
	geom.Push(v.v11(), t.v11());
	return geom;
}
// void Model2d::AddRectangle(const quad2 &in, const quad2 &out) {
// 	quad2 tex(0, 0, 1, 1);
// 	AddQuad(in, tex);
// 	float roundedleft = (in.p00 - out.p00).x;
// 	float roundedbottom = (in.p00 - out.p00).y;
// 	float roundedright = (out.p11 - in.p11).x;
// 	float roundedtop = (out.p11 - in.p11).y;
// 	AddQuad(quad2(in.p01, in.p11, out.p01 + glm::vec2(roundedleft, 0),
// 	              out.p11 - glm::vec2(roundedright, 0)),
// 	        tex);
// 	AddQuad(quad2(out.p00 + glm::vec2(roundedleft, 0),
// 	              out.p10 - glm::vec2(roundedright, 0), in.p00, in.p10),
// 	        tex);
// 	AddQuad(quad2(out.p00 + glm::vec2(0, roundedbottom), in.p00,
// 	              out.p01 - glm::vec2(0, roundedtop), in.p01),
// 	        tex);
// 	AddQuad(quad2(in.p10, out.p10 + glm::vec2(0, roundedbottom), in.p11,
// 	              out.p11 - glm::vec2(0, roundedtop)),
// 	        tex);

// 	if (glm::min(roundedright, roundedtop) != 0) {
// 		int quality = g_Graphics()->to_pixels(glm::max(roundedright, roundedtop)) /
// 4;

// 		for (int i = 0; i < quality; i++) {
// 			data->Add(in.p11, glm::vec2(0, 0));
// 			data->Add(in.p11 + glm::vec2(cos(i * M_PI_2 / quality) * roundedright,
// 			                                   sin(i * M_PI_2 / quality) *
// roundedtop),
// 			                glm::vec2(0, 0));
// 			data->Add(in.p11 +
// 			                    glm::vec2(cos((i + 1) * M_PI_2 / quality) *
// roundedright,
// 			                              sin((i + 1) * M_PI_2 / quality) *
// roundedtop),
// 			                glm::vec2(0, 0));
// 		}
// 	}
// 	if (glm::min(roundedright, roundedbottom) != 0) {
// 		int quality =
// 		    g_Graphics()->to_pixels(glm::max(roundedright, roundedbottom)) / 4;
// 		for (int i = 0; i < quality; i++) {
// 			data->Add(in.p10 +
// 			                    glm::vec2(cos(i * M_PI_2 / quality) * roundedright,
// 			                              -sin(i * M_PI_2 / quality) * roundedbottom),
// 			                glm::vec2(0, 0));
// 			data->Add(in.p10, glm::vec2(0, 0));
// 			data->Add(
// 			    in.p10 + glm::vec2(cos((i + 1) * M_PI_2 / quality) * roundedright,
// 			                       -sin((i + 1) * M_PI_2 / quality) * roundedbottom),
// 			    glm::vec2(0, 0));
// 		}
// 	}
// 	if (glm::min(roundedleft, roundedbottom) != 0) {
// 		int quality =
// 		    g_Graphics()->to_pixels(glm::max(roundedleft, roundedbottom)) / 4;
// 		for (int i = 0; i < quality; i++) {
// 			data->Add(in.p00, glm::vec2(0, 0));
// 			data->Add(in.p00 +
// 			                    glm::vec2(-cos(i * M_PI_2 / quality) * roundedleft,
// 			                              -sin(i * M_PI_2 / quality) * roundedbottom),
// 			                glm::vec2(0, 0));
// 			data->Add(
// 			    in.p00 + glm::vec2(-cos((i + 1) * M_PI_2 / quality) * roundedleft,
// 			                       -sin((i + 1) * M_PI_2 / quality) * roundedbottom),
// 			    glm::vec2(0, 0));
// 		}
// 	}
// 	if (glm::min(roundedleft, roundedtop) != 0) {
// 		int quality = g_Graphics()->to_pixels(glm::max(roundedleft, roundedtop)) /
// 4;
// 		for (int i = 0; i < quality; i++) {
// 			data->Add(in.p01 + glm::vec2(-cos(i * M_PI_2 / quality) * roundedleft,
// 			                                   sin(i * M_PI_2 / quality) *
// roundedtop),
// 			                glm::vec2(0, 0));
// 			data->Add(in.p01, glm::vec2(0, 0));
// 			data->Add(in.p01 +
// 			                    glm::vec2(-cos((i + 1) * M_PI_2 / quality) *
// roundedleft,
// 			                              sin((i + 1) * M_PI_2 / quality) *
// roundedtop),
// 			                glm::vec2(0, 0));
// 		}
// 	}
// }
// glm::vec3 vec2vec3(const glm::vec2 &v, float depth = 0) {
// 	return glm::vec3(-v.x, depth, v.y);
// }
// void Model3d::AddRectangle(const quad2 &in, const quad2 &out, float depth =
// 0) {
// 	quad2 tex(0, 0, 1, 1);
// 	glm::vec3 n(0, 1, 0);
// 	AddQuad(quad3(in, depth), n, tex);
// 	float roundedleft = (in.p00 - out.p00).x;
// 	float roundedbottom = (in.p00 - out.p00).y;
// 	float roundedright = (out.p11 - in.p11).x;
// 	float roundedtop = (out.p11 - in.p11).y;
// 	AddQuad(quad3(quad2(in.p01, in.p11, out.p01 + glm::vec2(roundedleft, 0),
// 	                    out.p11 - glm::vec2(roundedright, 0)),
// 	              depth),
// 	        n, tex);
// 	AddQuad(quad3(quad2(out.p00 + glm::vec2(roundedleft, 0),
// 	                    out.p10 - glm::vec2(roundedright, 0), in.p00, in.p10),
// 	              depth),
// 	        n, tex);
// 	AddQuad(quad3(quad2(out.p00 + glm::vec2(0, roundedbottom), in.p00,
// 	                    out.p01 - glm::vec2(0, roundedtop), in.p01),
// 	              depth),
// 	        n, tex);
// 	AddQuad(quad3(quad2(in.p10, out.p10 + glm::vec2(0, roundedbottom), in.p11,
// 	                    out.p11 - glm::vec2(0, roundedtop)),
// 	              depth),
// 	        n, tex);

// 	if (glm::min(roundedright, roundedtop) != 0) {
// 		int quality = g_Graphics()->to_pixels(glm::max(roundedright, roundedtop)) /
// 4;

// 		for (int i = 0; i < quality; i++) {
// 			data->Add(
// 			    vec2vec3(in.p11 +
// 			                 glm::vec2(cos((i + 1) * M_PI_2 / quality) * roundedright,
// 			                           sin((i + 1) * M_PI_2 / quality) * roundedtop),
// 			             depth),
// 			    n, glm::vec2(0, 0));
// 			data->Add(vec2vec3(in.p11, depth), n, glm::vec2(0, 0));
// 			data->Add(
// 			    vec2vec3(in.p11 + glm::vec2(cos(i * M_PI_2 / quality) * roundedright,
// 			                                sin(i * M_PI_2 / quality) * roundedtop),
// 			             depth),
// 			    n, glm::vec2(0, 0));
// 		}
// 	}
// 	if (glm::min(roundedright, roundedbottom) != 0) {
// 		int quality =
// 		    g_Graphics()->to_pixels(glm::max(roundedright, roundedbottom)) / 4;
// 		for (int i = 0; i < quality; i++) {
// 			data->Add(
// 			    vec2vec3(in.p10 + glm::vec2(cos(i * M_PI_2 / quality) * roundedright,
// 			                                -sin(i * M_PI_2 / quality) *
// roundedbottom),
// 			             depth),
// 			    n, glm::vec2(0, 0));
// 			data->Add(vec2vec3(in.p10, depth), n, glm::vec2(0, 0));
// 			data->Add(
// 			    vec2vec3(in.p10 +
// 			                 glm::vec2(cos((i + 1) * M_PI_2 / quality) * roundedright,
// 			                           -sin((i + 1) * M_PI_2 / quality) *
// roundedbottom),
// 			             depth),
// 			    n, glm::vec2(0, 0));
// 		}
// 	}
// 	if (glm::min(roundedleft, roundedbottom) != 0) {
// 		int quality =
// 		    g_Graphics()->to_pixels(glm::max(roundedleft, roundedbottom)) / 4;
// 		for (int i = 0; i < quality; i++) {
// 			data->Add(
// 			    vec2vec3(in.p00 +
// 			                 glm::vec2(-cos((i + 1) * M_PI_2 / quality) * roundedleft,
// 			                           -sin((i + 1) * M_PI_2 / quality) *
// roundedbottom),
// 			             depth),
// 			    n, glm::vec2(0, 0));
// 			data->Add(vec2vec3(in.p00, depth), n, glm::vec2(0, 0));
// 			data->Add(
// 			    vec2vec3(in.p00 + glm::vec2(-cos(i * M_PI_2 / quality) * roundedleft,
// 			                                -sin(i * M_PI_2 / quality) *
// roundedbottom),
// 			             depth),
// 			    n, glm::vec2(0, 0));
// 		}
// 	}
// 	if (glm::min(roundedleft, roundedtop) != 0) {
// 		int quality = g_Graphics()->to_pixels(glm::max(roundedleft, roundedtop)) /
// 4;
// 		for (int i = 0; i < quality; i++) {
// 			data->Add(
// 			    vec2vec3(in.p01 + glm::vec2(-cos(i * M_PI_2 / quality) * roundedleft,
// 			                                sin(i * M_PI_2 / quality) * roundedtop),
// 			             depth),
// 			    n, glm::vec2(0, 0));
// 			data->Add(vec2vec3(in.p01, depth), n, glm::vec2(0, 0));
// 			data->Add(
// 			    vec2vec3(in.p01 +
// 			                 glm::vec2(-cos((i + 1) * M_PI_2 / quality) * roundedleft,
// 			                           sin((i + 1) * M_PI_2 / quality) * roundedtop),
// 			             depth),
// 			    n, glm::vec2(0, 0));
// 		}
// 	}
// }
