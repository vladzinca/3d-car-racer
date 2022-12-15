#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace obj2D
{

    // Create triangle with given corners and color
    Mesh* CreateTriangle(const std::string& name, glm::vec3 corner1, glm::vec3 corner2, glm::vec3 corner3, glm::vec3 color, bool fill);
    // Create circle with given center, radius and color
    Mesh* CreateCircle(const std::string& name, glm::vec3 center, float radius, float triangleCount, glm::vec3 color, bool fill);
    // Create rectangle with given bottom left corner, width, height and color
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill);
    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
}
