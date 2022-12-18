#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace obj3D
{
    float computeArea(glm::vec3 A, glm::vec3 B, glm::vec3 C);

    int checkPoint(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 P);

    int checkAll(std::vector<glm::vec3> points, int pointCount, glm::vec3 P);

    int checkCollision(glm::vec3 A, glm::vec3 B, float aRadius, float bRadius);

    Mesh* CreatePlane(const std::string& name, glm::vec3 leftFarCorner, float sizeX, float sizeZ, glm::vec3 color);

    Mesh* CreateTree(const std::string& name, glm::vec3 leftBottomFarTrunkCorner, float trunkSize, float trunkHeight, float treeTopSize, glm::vec3 trunkColor, glm::vec3 leafColor);

    Mesh* CreateRoad(const std::string& name, std::vector<glm::vec3> points, int pointCount, float redDistance, float blueDistance, glm::vec3 color);

    Mesh* CreateCuboid(const std::string& name, glm::vec3 leftBottomFarCorner, float sizeX, float sizeY, float sizeZ, glm::vec3 color);

    // Create square with given bottom left corner, length and color
    Mesh* CreateCube(const std::string &name, glm::vec3 leftBottomFarCorner, float size, glm::vec3 color);
}
