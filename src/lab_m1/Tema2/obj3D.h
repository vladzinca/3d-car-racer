#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace obj3D
{
    float ComputeArea(glm::vec3 A, glm::vec3 B, glm::vec3 C);

    int CheckTriangle(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 P);

    int CheckAllTriangles(std::vector<glm::vec3> points, int pointCount, glm::vec3 P);

    int CheckCarCollision(glm::vec3 A, glm::vec3 B, float aRadius, float bRadius);

    Mesh* CreatePlane(const std::string& name, glm::vec3 leftFarCorner, float sizeX, float sizeZ, glm::vec3 color);

    Mesh* CreateRoad(const std::string& name, std::vector<glm::vec3> points, int pointCount, float redDistance, float blueDistance, glm::vec3 color);

    Mesh* CreateTree(const std::string& name, glm::vec3 leftBottomFarTrunkCorner, float trunkSize, float trunkHeight, float treeTopSize, glm::vec3 trunkColor, glm::vec3 leafColor);

    Mesh* CreateCar(const std::string& name, glm::vec3 leftBottomFarCorner, float sizeX, float sizeY, float sizeZ, glm::vec3 color);

}
