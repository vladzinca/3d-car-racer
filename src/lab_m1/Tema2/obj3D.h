#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace obj3D
{
    Mesh* CreateTree(const std::string& name, glm::vec3 leftBottomFarTrunkCorner, float trunkSize, float trunkHeight, float treeTopSize, glm::vec3 trunkColor, glm::vec3 leafColor);

    Mesh* GenerateCompleteRoad(const std::string& name, std::vector<glm::vec3> points, int pointCount, glm::vec3 color);

    Mesh* CreateCuboid(const std::string& name, glm::vec3 leftBottomFarCorner, float sizeX, float sizeY, float sizeZ, glm::vec3 color);

    // Create square with given bottom left corner, length and color
    Mesh* CreateCube(const std::string &name, glm::vec3 leftBottomFarCorner, float size, glm::vec3 color);
}
