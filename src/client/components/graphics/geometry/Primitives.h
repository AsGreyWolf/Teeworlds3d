#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <client/components/graphics/geometry/Geometry2d.h>
#include <client/components/graphics/geometry/Geometry3d.h>

Geometry3d Point(const glm::vec3 &v, const glm::vec3 &n = glm::vec3(0, 0, 0),
                 const glm::vec2 &t = glm::vec2(0, 0));
Geometry3d Line(const glm::vec3 &v1, const glm::vec3 &v2,
                const glm::vec3 &n1 = glm::vec3(0, 0, 0),
                const glm::vec3 &n2 = glm::vec3(0, 0, 0),
                const glm::vec2 &t1 = glm::vec2(0, 0),
                const glm::vec2 &t2 = glm::vec2(1, 1));
Geometry3d Quad(const quad3 &v, const glm::vec3 &n = glm::vec3(0, 0, 0),
                const quad2 &t = quad2(0, 0, 1, 1));
Geometry2d Point(const glm::vec2 &v, const glm::vec2 &t = glm::vec2(0, 0));
Geometry2d Line(const glm::vec2 &v1, const glm::vec2 &v2,
                const glm::vec2 &t1 = glm::vec2(0, 0),
                const glm::vec2 &t2 = glm::vec2(1, 1));
Geometry2d Quad(const quad2 &v, const quad2 &t = quad2(0, 0, 1, 1));

#endif
