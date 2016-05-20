#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <client/components/graphics/geometry/Geometry3d.h>

Geometry3d ObjModel(const std::string &filename,
                    const glm::vec3 &position = glm::vec3(0, 0, 0));

#endif
