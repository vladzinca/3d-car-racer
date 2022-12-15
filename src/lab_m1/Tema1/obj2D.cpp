#include "obj2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* obj2D::CreateTriangle(
    const std::string& name,
    glm::vec3 corner1,
    glm::vec3 corner2,
    glm::vec3 corner3,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner1, color),
        VertexFormat(corner2, color),
        VertexFormat(corner3, color),
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1 };

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(2);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* obj2D::CreateCircle(
    const std::string& name,
    glm::vec3 center,
    float radius,
    float triangleCount,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center, color),
    };

    for (int i = 0; i <= triangleCount; i++)
    {
        vertices.push_back(VertexFormat(glm::vec3(center.x + (radius * cos(i * 2 * M_PI / triangleCount)), center.y + (radius * sin(i * 2 * M_PI / triangleCount)), 0), color));
    }

    Mesh* circle = new Mesh(name);
    std::vector<unsigned int> indices;

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        for (int i = 0; i < triangleCount; i++) {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i + 2); // 0, 1, 2, 0, 2, 3, 0, 3, 4, ...
        }
    }

    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* obj2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float width,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(2);
        indices.push_back(0);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* obj2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}
