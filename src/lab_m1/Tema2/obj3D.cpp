#include "obj3D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

float obj3D::ComputeArea(glm::vec3 A, glm::vec3 B, glm::vec3 C)
{
    return glm::length(glm::cross(B - A, C - A)) / 2.0f;
}

int obj3D::CheckTriangle(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 P)
{
    float totalArea = ComputeArea(A, B, C);
    float area1 = ComputeArea(A, C, P);
    float area2 = ComputeArea(A, B, P);
    float area3 = ComputeArea(B, C, P);

    if (abs((area1 + area2 + area3) - totalArea) < 0.0001)
        return 1;

    return 0;
}

int obj3D::CheckAllTriangles(std::vector<glm::vec3> points, int pointCount, glm::vec3 P)
{
    std::vector<glm::vec3> vertices;

    float redDistance = 2.5f;
    float blueDistance = 1.5f;

    for (int i = 0; i < pointCount - 1; i++)
    {
        int tmp = i + 1;
        glm::vec3 d = points[tmp] - points[i];
        d = glm::normalize(d);

        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 p = glm::cross(d, up);
        
        glm::vec3 r = points[i] + redDistance * p;
        glm::vec3 b = points[i] - blueDistance * p;

        vertices.push_back(r);
        vertices.push_back(b);
    }

    int tmp = pointCount - 1;
    glm::vec3 d = points[0] - points[tmp];
    d = glm::normalize(d);

    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 p = glm::cross(d, up);

    glm::vec3 r = points[tmp] + redDistance * p;
    glm::vec3 b = points[tmp] - blueDistance * p;

    vertices.push_back(r);
    vertices.push_back(b);

    for (int i = 0; i < pointCount - 1; i++)
    {
        int tmp_a = 2 * i;
        int tmp_b = 2 * i + 1;
        int tmp_c = 2 * i + 2;
        int tmp_d = 2 * i + 3;

        if (CheckTriangle(vertices[tmp_a], vertices[tmp_b], vertices[tmp_d], P))
            return 1;
        if (CheckTriangle(vertices[tmp_a], vertices[tmp_c], vertices[tmp_d], P))
            return 1;
    }

    int tmp_a = 2 * (pointCount - 1);
    int tmp_b = 2 * (pointCount - 1) + 1;

    if (CheckTriangle(vertices[tmp_a], vertices[tmp_b], vertices[1], P))
        return 1;
    if (CheckTriangle(vertices[tmp_a], vertices[0], vertices[1], P))
        return 1;

    return 0;
}

int obj3D::CheckCarCollision(glm::vec3 A, glm::vec3 B, float aRadius, float bRadius)
{
    if (sqrt(pow((A.x - B.x), 2) + pow((A.y - B.y), 2) + pow((A.z - B.z), 2)) <= aRadius + bRadius)
        return 1;

    return 0;
}

Mesh* obj3D::CreatePlane(
    const std::string& name,
    glm::vec3 leftFarCorner,
    float sizeX,
    float sizeZ,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices;

    for (int j = 0; j < 1000; j++)
        for (int i = 0; i < 1000; i++)
            vertices.push_back(VertexFormat(leftFarCorner + glm::vec3((float)i / 999.0f * sizeX, 
                                                                      0,
                                                                      (float)j / 999.0f * sizeZ),
                                            glm::vec3(1), color));

    Mesh* plane = new Mesh(name);
    std::vector<unsigned int> indices;

    for (int i = 0; i < 999; i++)
    {
        for (int j = 0; j < 999; j++)
        {
            indices.push_back(i * 1000 + j);
            indices.push_back(i * 1000 + 1 + j);
            indices.push_back((i + 1) * 1000 + 1 + j);

            indices.push_back(i * 1000 + j);
            indices.push_back((i + 1) * 1000 + j);
            indices.push_back((i + 1) * 1000 + 1 + j);
        }
    }

    plane->InitFromData(vertices, indices);
    return plane;
}

Mesh* obj3D::CreateRoad(
    const std::string& name,
    std::vector<glm::vec3> points,
    int pointCount,
    float redDistance,
    float blueDistance,
    glm::vec3 color)
{
    std::vector<glm::vec3> redPoints;
    std::vector<glm::vec3> bluePoints;

    for (int i = 0; i < pointCount - 1; i++)
    {
        int tmp = i + 1;
        glm::vec3 d = points[tmp] - points[i];
        d = glm::normalize(d);

        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 p = glm::cross(d, up);

        redPoints.push_back(points[i] + redDistance * p);
        bluePoints.push_back(points[i] - blueDistance * p);
    }

    int tmp = pointCount - 1;
    glm::vec3 d = points[0] - points[tmp];
    d = glm::normalize(d);

    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 p = glm::cross(d, up);

    redPoints.push_back(points[tmp] + redDistance * p);
    bluePoints.push_back(points[tmp] - blueDistance * p);

    std::vector<VertexFormat> vertices;

    for (int i = 0; i < pointCount - 1; i++)
    {
        tmp = i + 1;
        glm::vec3 dRed = redPoints[tmp] - redPoints[i];
        glm::vec3 dBlue = bluePoints[tmp] - bluePoints[i];

        for (int j = 0; j < 1000; j++)
        {
            vertices.push_back(VertexFormat(redPoints[i] + ((float)j / 1000.0f) * dRed, glm::vec3(1), color));
            vertices.push_back(VertexFormat(bluePoints[i] + ((float)j / 1000.0f) * dBlue, glm::vec3(1), color));
        }
    }

    tmp = pointCount - 1;
    glm::vec3 dRed = redPoints[0] - redPoints[tmp];
    glm::vec3 dBlue = bluePoints[0] - bluePoints[tmp];

    for (int j = 0; j < 1000; j++)
    {
        vertices.push_back(VertexFormat(redPoints[tmp] + ((float)j / 1000.0f) * dRed, glm::vec3(1), color));
        vertices.push_back(VertexFormat(bluePoints[tmp] + ((float)j / 1000.0f) * dBlue, glm::vec3(1), color));
    }

    Mesh* road = new Mesh(name);
    std::vector<unsigned int> indices;

    for (int i = 0; i < pointCount - 1; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            indices.push_back(2000 * i + 2 * j);
            indices.push_back(2000 * i + 1 + 2 * j);
            indices.push_back(2000 * i + 3 + 2 * j);

            indices.push_back(2000 * i + 2 * j);
            indices.push_back(2000 * i + 2 + 2 * j);
            indices.push_back(2000 * i + 3 + 2 * j);
        }
    }

    for (int j = 0; j < 999; j++)
    {
        indices.push_back(2000 * (pointCount - 1) + 2 * j);
        indices.push_back(2000 * (pointCount - 1) + 1 + 2 * j);
        indices.push_back(2000 * (pointCount - 1) + 3 + 2 * j);

        indices.push_back(2000 * (pointCount - 1) + 2 * j);
        indices.push_back(2000 * (pointCount - 1) + 2 + 2 * j);
        indices.push_back(2000 * (pointCount - 1) + 3 + 2 * j);
    }

    indices.push_back(2000 * (pointCount - 1) + 2 * 999);
    indices.push_back(2000 * (pointCount - 1) + 1 + 2 * 999);
    indices.push_back(1);

    indices.push_back(2000 * (pointCount - 1) + 2 * 999);
    indices.push_back(0);
    indices.push_back(1);

    road->InitFromData(vertices, indices);
    return road;
}

Mesh* obj3D::CreateTree(
    const std::string& name,
    glm::vec3 leftBottomFarTrunkCorner,
    float trunkSize,
    float trunkHeight,
    float treeTopSize,
    glm::vec3 trunkColor,
    glm::vec3 leafColor)
{
    std::vector<VertexFormat> vertices;

    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner,
                                    glm::vec3(1), trunkColor));
    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner + glm::vec3(trunkSize, 0, 0),
                                    glm::vec3(1), trunkColor));
    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner + glm::vec3(trunkSize, 0, trunkSize),
                                    glm::vec3(1), trunkColor));
    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner + glm::vec3(0, 0, trunkSize),
                                    glm::vec3(1), trunkColor));

    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner + glm::vec3(0, trunkHeight, 0),
                                    glm::vec3(1), trunkColor));
    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner + glm::vec3(trunkSize, trunkHeight, 0),
                                    glm::vec3(1), trunkColor));
    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner + glm::vec3(trunkSize, trunkHeight, trunkSize),
                                    glm::vec3(1), trunkColor));
    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner + glm::vec3(0, trunkHeight, trunkSize),
                                    glm::vec3(1), trunkColor));

    glm::vec3 leftBottomFarTreeTopCorner = leftBottomFarTrunkCorner +
                                           glm::vec3(-((treeTopSize - trunkSize) / 2.0f),
                                                     trunkHeight,
                                                     -((treeTopSize - trunkSize) / 2.0f));

    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner,
                                    glm::vec3(1), leafColor));
    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner + glm::vec3(treeTopSize, 0, 0),
                                    glm::vec3(1), leafColor));
    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner + glm::vec3(treeTopSize, 0, treeTopSize),
                                    glm::vec3(1), leafColor));
    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner + glm::vec3(0, 0, treeTopSize),
                                    glm::vec3(1), leafColor));

    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner + glm::vec3(0, treeTopSize, 0),
                                    glm::vec3(1), leafColor));
    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner + glm::vec3(treeTopSize, treeTopSize, 0),
                                    glm::vec3(1), leafColor));
    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner + glm::vec3(treeTopSize, treeTopSize, treeTopSize),
                                    glm::vec3(1), leafColor));
    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner + glm::vec3(0, treeTopSize, treeTopSize),
                                    glm::vec3(1), leafColor));

    Mesh* tree = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          3, 0, 2,

                                          3, 2, 6,
                                          7, 3, 6,

                                          2, 1, 5,
                                          6, 2, 5,

                                          1, 0, 4,
                                          5, 1, 4,

                                          0, 3, 7,
                                          4, 0, 7,

                                          4, 5, 6,
                                          7, 4, 6,

                                          8, 9, 10,
                                          11, 8, 10,

                                          11, 10, 14,
                                          15, 11, 14,

                                          10, 9, 13,
                                          14, 10, 13,

                                          9, 8, 12,
                                          13, 9, 12,

                                          8, 11, 15,
                                          12, 8, 15,

                                          12, 13, 14,
                                          15, 12, 14 };

    tree->InitFromData(vertices, indices);
    return tree;
}

Mesh* obj3D::CreateCar(
    const std::string& name,
    glm::vec3 leftBottomFarCorner,
    float sizeX,
    float sizeY,
    float sizeZ,
    glm::vec3 color)
{
    glm::vec3 corner = leftBottomFarCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner,  glm::vec3(1), color),
        VertexFormat(corner + glm::vec3(sizeX, 0, 0), glm::vec3(1), color),
        VertexFormat(corner + glm::vec3(sizeX, sizeY, 0), glm::vec3(1), color),
        VertexFormat(corner + glm::vec3(0, sizeY, 0), glm::vec3(1), color),

        VertexFormat(corner + glm::vec3(0, 0, sizeZ), glm::vec3(1), color),
        VertexFormat(corner + glm::vec3(sizeX, 0, sizeZ), glm::vec3(1), color),
        VertexFormat(corner + glm::vec3(sizeX, sizeY, sizeZ), glm::vec3(1), color),
        VertexFormat(corner + glm::vec3(0, sizeY, sizeZ), glm::vec3(1), color),
    };

    Mesh* cuboid = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          3, 0, 2,

                                          0, 1, 5,
                                          4, 0, 5,

                                          1, 2, 6,
                                          5, 1, 6,

                                          2, 3, 7,
                                          6, 2, 7,

                                          3, 0, 4,
                                          7, 3, 4,

                                          4, 5, 6,
                                          7, 4, 6 };

    cuboid->InitFromData(vertices, indices);
    return cuboid;
}
