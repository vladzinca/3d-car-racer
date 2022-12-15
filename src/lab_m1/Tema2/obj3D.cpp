#include "obj3D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* obj3D::GenerateCompleteRoad(
    const std::string& name,
    std::vector<glm::vec3> points,
    int pointCount,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices;

    float redDistance = 0.6f;
    float blueDistance = 0.45f;

    for (int i = 0; i < pointCount - 1; i++)
    {
        glm::vec3 d = points[i + 1] - points[i];
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 p = glm::cross(d, up);
        glm::vec3 r = points[i] + redDistance * p;
        glm::vec3 b = points[i] - blueDistance * p;
        vertices.push_back(VertexFormat(r, glm::vec3(1), color));
        vertices.push_back(VertexFormat(b, glm::vec3(1), color));
    }

    glm::vec3 d = points[0] - points[pointCount - 1];
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 p = glm::cross(d, up);
    glm::vec3 r = points[pointCount - 1] + redDistance * p;
    glm::vec3 b = points[pointCount - 1] - blueDistance * p;
    vertices.push_back(VertexFormat(r, glm::vec3(1), color));
    vertices.push_back(VertexFormat(b, glm::vec3(1), color));

    Mesh* road = new Mesh(name);
    std::vector<unsigned int> indices;

    for (int i = 0; i < pointCount - 1; i++)
    {
        indices.push_back(2 * i);
        indices.push_back(2 * i + 1);
        indices.push_back(2 * i + 3);

        indices.push_back(2 * i);
        indices.push_back(2 * i + 2);
        indices.push_back(2 * i + 3);
    }

    indices.push_back(2 * (pointCount - 1));
    indices.push_back(2 * (pointCount - 1) + 1);
    indices.push_back(1);

    indices.push_back(2 * (pointCount - 1));
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
