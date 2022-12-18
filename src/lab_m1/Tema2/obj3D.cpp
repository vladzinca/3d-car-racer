#include "obj3D.h"

//#include <iostream> // sterge
#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

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
            vertices.push_back(VertexFormat(leftFarCorner + glm::vec3((float)i / 999.0f * sizeX, 0, (float)j / 999.0f * sizeZ), glm::vec3(1), color));

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

    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner, glm::vec3(1), trunkColor));
    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner + glm::vec3(trunkSize, 0, 0), glm::vec3(1), trunkColor));
    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner + glm::vec3(trunkSize, 0, trunkSize), glm::vec3(1), trunkColor));
    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner + glm::vec3(0, 0, trunkSize), glm::vec3(1), trunkColor));

    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner + glm::vec3(0, trunkHeight, 0), glm::vec3(1), trunkColor));
    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner + glm::vec3(trunkSize, trunkHeight, 0), glm::vec3(1), trunkColor));
    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner + glm::vec3(trunkSize, trunkHeight, trunkSize), glm::vec3(1), trunkColor));
    vertices.push_back(VertexFormat(leftBottomFarTrunkCorner + glm::vec3(0, trunkHeight, trunkSize), glm::vec3(1), trunkColor));

    glm::vec3 leftBottomFarTreeTopCorner = leftBottomFarTrunkCorner + glm::vec3(-((treeTopSize - trunkSize) / 2.0f), trunkHeight, -((treeTopSize - trunkSize) / 2.0f));

    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner, glm::vec3(1), leafColor));
    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner + glm::vec3(treeTopSize, 0, 0), glm::vec3(1), leafColor));
    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner + glm::vec3(treeTopSize, 0, treeTopSize), glm::vec3(1), leafColor));
    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner + glm::vec3(0, 0, treeTopSize), glm::vec3(1), leafColor));

    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner + glm::vec3(0, treeTopSize, 0), glm::vec3(1), leafColor));
    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner + glm::vec3(treeTopSize, treeTopSize, 0), glm::vec3(1), leafColor));
    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner + glm::vec3(treeTopSize, treeTopSize, treeTopSize), glm::vec3(1), leafColor));
    vertices.push_back(VertexFormat(leftBottomFarTreeTopCorner + glm::vec3(0, treeTopSize, treeTopSize), glm::vec3(1), leafColor));

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

Mesh* obj3D::GenerateCompleteRoad(
    const std::string& name,
    std::vector<glm::vec3> points,
    int pointCount,
    glm::vec3 color,
    bool fill)
{
    std::vector<glm::vec3> redPoints;
    std::vector<glm::vec3> bluePoints;

    float redDistance = 2.5f;
    float blueDistance = 1.5f;

    for (int i = 0; i < pointCount - 1; i++)
    {
        glm::vec3 d = points[i + 1] - points[i];
        d = glm::normalize(d);
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 p = glm::cross(d, up);
        redPoints.push_back(points[i] + redDistance * p);
        bluePoints.push_back(points[i] - blueDistance * p);
    }

    glm::vec3 d = points[0] - points[pointCount - 1];
    d = glm::normalize(d);
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 p = glm::cross(d, up);
    redPoints.push_back(points[pointCount - 1] + redDistance * p);
    bluePoints.push_back(points[pointCount - 1] - blueDistance * p);

    std::vector<VertexFormat> vertices;
    for (int i = 0; i < pointCount - 1; i++)
    {
        glm::vec3 dRed = redPoints[i + 1] - redPoints[i];
        glm::vec3 dBlue = bluePoints[i + 1] - bluePoints[i];
        //int j = 0;
        for (int j = 0; j < 1000; j++)
        {
            vertices.push_back(VertexFormat(redPoints[i] + ((float)j / 1000.0f) * dRed, glm::vec3(1), color));
            vertices.push_back(VertexFormat(bluePoints[i] + ((float)j / 1000.0f) * dBlue, glm::vec3(1), color));
        }
    }

    glm::vec3 dRed = redPoints[0] - redPoints[pointCount - 1];
    glm::vec3 dBlue = bluePoints[0] - bluePoints[pointCount - 1];
    //int j = 0;
    for (int j = 0; j < 1000; j++)
    {
        vertices.push_back(VertexFormat(redPoints[pointCount - 1] + ((float)j / 1000.0f) * dRed, glm::vec3(1), color));
        vertices.push_back(VertexFormat(bluePoints[pointCount - 1] + ((float)j / 1000.0f) * dBlue, glm::vec3(1), color));
    }

    Mesh* road = new Mesh(name);
    std::vector<unsigned int> indices;

    //for (int i = 0; i < pointCount - 1; i++)
    //{
    //    indices.push_back(2 * i);
    //    indices.push_back(2 * i + 1);
    //    indices.push_back(2 * i + 3);

    //    indices.push_back(2 * i);
    //    indices.push_back(2 * i + 2);
    //    indices.push_back(2 * i + 3);
    //}

    //indices.push_back(2 * (pointCount - 1));
    //indices.push_back(2 * (pointCount - 1) + 1);
    //indices.push_back(1);

    //indices.push_back(2 * (pointCount - 1));
    //indices.push_back(0);
    //indices.push_back(1);

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

Mesh* obj3D::CreateCuboid(
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

Mesh* obj3D::CreateCube(
    const std::string &name,
    glm::vec3 leftBottomFarCorner,
    float size,
    glm::vec3 color)
{
    glm::vec3 corner = leftBottomFarCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner,  glm::vec3(1), color),
        VertexFormat(corner + glm::vec3(size, 0, 0), glm::vec3(1), color),
        VertexFormat(corner + glm::vec3(size, size, 0), glm::vec3(1), color),
        VertexFormat(corner + glm::vec3(0, size, 0), glm::vec3(1), color),

        VertexFormat(corner + glm::vec3(0, 0, size), glm::vec3(1), color),
        VertexFormat(corner + glm::vec3(size, 0, size), glm::vec3(1), color),
        VertexFormat(corner + glm::vec3(size, size, size), glm::vec3(1), color),
        VertexFormat(corner + glm::vec3(0, size, size), glm::vec3(1), color),
    };

    Mesh* cube = new Mesh(name);
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

    cube->InitFromData(vertices, indices);
    return cube;
}
