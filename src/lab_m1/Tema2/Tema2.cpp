#include "lab_m1/Tema2/tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <cmath> // vezi daca poti scoate

#include "lab_m1/Tema2/obj3D.h"
#include "lab_m1/Tema2/transf3D.h"
#include "lab_m1/Tema2/hw_camera.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}

float Tema2::computeArea(glm::vec3 A, glm::vec3 B, glm::vec3 C)
{
    return  glm::length(glm::cross(B - A, C - A)) / 2.0f;
}

int Tema2::checkPoint(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 P)
{
    float totalArea = computeArea(A, B, C);
    float area1 = computeArea(A, C, P);
    float area2 = computeArea(A, B, P);
    float area3 = computeArea(B, C, P);

    if (abs((area1 + area2 + area3) - totalArea) < 0.0001)
        return 1;

    return 0;
}

int Tema2::checkAll(std::vector<glm::vec3> points, int pointCount, glm::vec3 P)
{
    std::vector<glm::vec3> vertices;

    float redDistance = 2.5f;
    float blueDistance = 1.5f;

    for (int i = 0; i < pointCount - 1; i++)
    {
        glm::vec3 d = points[i + 1] - points[i];
        d = glm::normalize(d);
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 p = glm::cross(d, up);
        glm::vec3 r = points[i] + redDistance * p;
        glm::vec3 b = points[i] - blueDistance * p;
        vertices.push_back(r);
        vertices.push_back(b);
    }

    glm::vec3 d = points[0] - points[pointCount - 1];
    d = glm::normalize(d);
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 p = glm::cross(d, up);
    glm::vec3 r = points[pointCount - 1] + redDistance * p;
    glm::vec3 b = points[pointCount - 1] - blueDistance * p;
    vertices.push_back(r);
    vertices.push_back(b);

    for (int i = 0; i < pointCount - 1; i++)
    {
        if (checkPoint(vertices[2 * i], vertices[2 * i + 1], vertices[2 * i + 3], P))
            return 1;
        if (checkPoint(vertices[2 * i], vertices[2 * i + 2], vertices[2 * i + 3], P))
            return 1;
    }

    if (checkPoint(vertices[2 * (pointCount - 1)], vertices[2 * (pointCount - 1) + 1], vertices[1], P))
        return 1;
    if (checkPoint(vertices[2 * (pointCount - 1)], vertices[0], vertices[1], P))
        return 1;

    return 0;
}

int Tema2::checkCollision(glm::vec3 A, glm::vec3 B, float aRadius, float bRadius)
{
    if (sqrt(pow((A.x - B.x), 2) + pow((A.y - B.y), 2) + pow((A.z - B.z), 2)) <= aRadius + bRadius)
        return 1;
    return 0;
}

void Tema2::Init()
{
    
    //{
    //    Mesh* mesh = new Mesh("box");
    //    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    //    meshes[mesh->GetMeshID()] = mesh;
    //}

    //// Create a simple cube
    //{
    //    vector<VertexFormat> vertices
    //    {
    //        VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1), glm::vec3(1, 0, 1)),
    //        VertexFormat(glm::vec3( 1, -1,  1), glm::vec3(1), glm::vec3(1, 0, 1)),
    //        VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1), glm::vec3(1, 0, 1)),
    //        VertexFormat(glm::vec3( 1,  1,  1), glm::vec3(1), glm::vec3(1, 0, 1)),
    //        VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1), glm::vec3(1, 0, 1)),
    //        VertexFormat(glm::vec3( 1, -1, -1), glm::vec3(1), glm::vec3(1, 0, 1)),
    //        VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1), glm::vec3(1, 0, 1)),
    //        VertexFormat(glm::vec3( 1,  1, -1), glm::vec3(1), glm::vec3(1, 0, 1)),
    //    };

    //    vector<unsigned int> indices =
    //    {
    //        0, 1, 2,        1, 3, 2,
    //        2, 3, 7,        2, 7, 6,
    //        1, 7, 3,        1, 5, 7,
    //        6, 7, 4,        7, 5, 4,
    //        0, 4, 1,        1, 4, 5,
    //        2, 6, 4,        0, 2, 4,
    //    };

    //    CreateMesh("cube", vertices, indices);
    //}

    camera = new implement::Camera();
    camera->Set(glm::vec3(0, 2, 2), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    miniCamera = new implement::Camera();
    miniCamera->Set(glm::vec3(0, 15, 0.1f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    glm::vec3 cameraPosition = glm::vec3(0, 2, 2);
    glm::vec3 miniCameraPosition = glm::vec3(0, 15, 0.1f);

    translateX = 0;
    translateZ = 0;

    position = glm::vec3(-0.25f, 0.15f, -0.5f);

    angularStepOY = 0;

    forward = glm::vec3(0, 0, -1);

    fov = 60.0f;
    zNear = 0.01f;
    zFar = 200.0f;

    left = -15.0f;
    right = 15.0f;
    bottom = -7.5f;
    up = 7.5f;

    timeFreeze = 0;
    initialTime = 0;

    //projectionMatrix = glm::ortho(left, right, bottom, up, zNear, zFar);
    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, zNear, zFar);

    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, (int)(resolution.x / 4.0f), (int)(resolution.y / 4.0f));

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader *shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;

        Shader* shader2 = new Shader("LabShader2");
        shader2->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader2.glsl"), GL_VERTEX_SHADER);
        shader2->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader2.glsl"), GL_FRAGMENT_SHADER);
        shader2->CreateAndLink();
        shaders[shader2->GetName()] = shader2;
    }

    //{
    //    Mesh* mesh = new Mesh("plane");
    //    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
    //    meshes[mesh->GetMeshID()] = mesh;
    //}

    //color = glm::vec3(0, 0, 1);
    //Mesh* myCube = obj3D::CreateCube("myCube", glm::vec3(0, 0, 0), 1, glm::vec3(1, 1, 0));
    //AddMeshToList(myCube);

    Mesh* green_plane = obj3D::CreateCuboid("green_plane", glm::vec3(-64, 0, -64), 128, 0.1f, 128, glm::vec3(0.5f, 0.8f, 0.3f));
    AddMeshToList(green_plane);

    Mesh* horizon_top = obj3D::CreateCuboid("horizon_top", glm::vec3(-64, 64, -64), 128, 0.1f, 128, glm::vec3(0.5f, 0.8f, 0.9f));
    AddMeshToList(horizon_top);

    Mesh* horizon_back = obj3D::CreateCuboid("horizon_back", glm::vec3(-64, 0, 64), 128, 64, 0.1f, glm::vec3(0.5f, 0.8f, 0.9f));
    AddMeshToList(horizon_back);

    Mesh* horizon_right = obj3D::CreateCuboid("horizon_right", glm::vec3(64, 0, -64), 0.1f, 64, 128, glm::vec3(0.5f, 0.8f, 0.9f));
    AddMeshToList(horizon_right);

    Mesh* horizon_front = obj3D::CreateCuboid("horizon_front", glm::vec3(-64, 0, -64), 128, 64, 0.1f, glm::vec3(0.5f, 0.8f, 0.9f));
    AddMeshToList(horizon_front);

    Mesh* horizon_left = obj3D::CreateCuboid("horizon_left", glm::vec3(-64, 0, -64), 0.1f, 64, 128, glm::vec3(0.5f, 0.8f, 0.9f));
    AddMeshToList(horizon_left);

    roadPointCount = 40;
    
    roadPoints.push_back(glm::vec3(33.65f, 0.13f, 5.15f)); // A
    roadPoints.push_back(glm::vec3(30.53f, 0.13f, 8.93f));
    roadPoints.push_back(glm::vec3(26.83f, 0.13f, 13.31f));
    roadPoints.push_back(glm::vec3(21.04f, 0.13f, 17.59f));

    roadPoints.push_back(glm::vec3(15.59f, 0.13f, 18.85f)); // E
    roadPoints.push_back(glm::vec3(10.89f, 0.13f, 18.43f));
    roadPoints.push_back(glm::vec3(5.85f, 0.13f, 15.91f));
    roadPoints.push_back(glm::vec3(3.0f, 0.13f, 11.8f));

    roadPoints.push_back(glm::vec3(1.74f, 0.13f, 7.44f)); // I
    roadPoints.push_back(glm::vec3(0.4f, 0.13f, 2.15f));
    roadPoints.push_back(glm::vec3(-0.61f, 0.13f, -3.38f));
    roadPoints.push_back(glm::vec3(-1.78f, 0.13f, -8.42f));

    roadPoints.push_back(glm::vec3(-3.96f, 0.13f, -13.7f)); // M
    roadPoints.push_back(glm::vec3(-7.15f, 0.13f, -16.81f));
    roadPoints.push_back(glm::vec3(-12.02f, 0.13f, -17.9f));
    roadPoints.push_back(glm::vec3(-18.06f, 0.13f, -18.23f));

    roadPoints.push_back(glm::vec3(-23.09f, 0.13f, -19.83f)); // Q
    roadPoints.push_back(glm::vec3(-27.37f, 0.13f, -22.93f));
    roadPoints.push_back(glm::vec3(-29.3f, 0.13f, -27.3f));
    roadPoints.push_back(glm::vec3(-30.29f, 0.13f, -31.97f));

    roadPoints.push_back(glm::vec3(-30.2f, 0.13f, -36.97f)); // U
    roadPoints.push_back(glm::vec3(-28.87f, 0.13f, -40.66f));
    roadPoints.push_back(glm::vec3(-26.14f, 0.13f, -43.21f));
    roadPoints.push_back(glm::vec3(-21.51f, 0.13f, -44.06f));

    roadPoints.push_back(glm::vec3(-15.28f, 0.13f, -43.11f)); // A1
    roadPoints.push_back(glm::vec3(-9.51f, 0.13f, -41.79f));
    roadPoints.push_back(glm::vec3(-5.0f, 0.13f, -40.0f));
    roadPoints.push_back(glm::vec3(-0.35f, 0.13f, -36.59f));

    roadPoints.push_back(glm::vec3(3.99f, 0.13f, -32.44f)); // E1
    roadPoints.push_back(glm::vec3(8.34f, 0.13f, -28.0f));
    roadPoints.push_back(glm::vec3(11.73f, 0.13f, -23.28f));
    roadPoints.push_back(glm::vec3(15.89f, 0.13f, -18.93f));

    roadPoints.push_back(glm::vec3(20.71f, 0.13f, -16.2f)); // I1
    roadPoints.push_back(glm::vec3(25.81f, 0.13f, -14.31f));
    roadPoints.push_back(glm::vec3(30.15f, 0.13f, -12.8f));
    roadPoints.push_back(glm::vec3(34.5f, 0.13f, -11.85f));

    roadPoints.push_back(glm::vec3(37.8f, 0.13f, -10.06f)); // M1
    roadPoints.push_back(glm::vec3(39.69f, 0.13f, -6.85f));
    roadPoints.push_back(glm::vec3(38.74f, 0.13f, -2.69f));
    roadPoints.push_back(glm::vec3(36.57f, 0.13f, 1.09f));

    purpleEnemyDistance = ((float)(rand() % 15 + 5)) / 10.0f;
    yellowEnemyDistance = ((float)(rand() % 5 + 5)) / 10.0f;
    
    for (int i = 0; i < 39; i++)
    {
        glm::vec3 d = glm::normalize(roadPoints[i + 1] - roadPoints[i]);
        directions.push_back(d);
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 p = glm::cross(d, up);
        glm::vec3 r = roadPoints[i] + purpleEnemyDistance * p;
        glm::vec3 b = roadPoints[i] - yellowEnemyDistance * p;
        purpleEnemyPoints.push_back(r);
        yellowEnemyPoints.push_back(b);
    }
    glm::vec3 d = glm::normalize(roadPoints[0] - roadPoints[39]);
    directions.push_back(d);
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 p = glm::cross(d, up);
    glm::vec3 r = roadPoints[39] + purpleEnemyDistance * p;
    glm::vec3 b = roadPoints[39] - yellowEnemyDistance * p;
    purpleEnemyPoints.push_back(r);
    yellowEnemyPoints.push_back(b);

    for (int i = 0; i < 39; i++)
    {
        glm::vec3 d1 = glm::normalize(purpleEnemyPoints[i + 1] - purpleEnemyPoints[i]);
        glm::vec3 d2 = glm::normalize(yellowEnemyPoints[i + 1] - yellowEnemyPoints[i]);
        purpleEnemyDirections.push_back(d1);
        yellowEnemyDirections.push_back(d2);
    }
    purpleEnemyDirections.push_back(glm::normalize(purpleEnemyPoints[0] - purpleEnemyPoints[39]));
    yellowEnemyDirections.push_back(glm::normalize(yellowEnemyPoints[0] - yellowEnemyPoints[39]));

    cx = 0.25f;
    cz = 0.5f;

    purpleEnemy_counter = 11;
    purpleEnemy_forward = purpleEnemyDirections[10];
    purpleEnemy_position = purpleEnemyPoints[10];

    purpleEnemy_translateX = purpleEnemy_position.x - 0.25f;
    purpleEnemy_translateZ = purpleEnemy_position.z - 0.5f;

    purpleEnemy_angularStepOY = atan2(purpleEnemy_forward.x, purpleEnemy_forward.z) - atan2(0, -1);


    yellowEnemy_counter = 11;
    yellowEnemy_forward = -yellowEnemyDirections[11];
    yellowEnemy_position = yellowEnemyPoints[12];

    yellowEnemy_translateX = yellowEnemy_position.x - 0.25f;
    yellowEnemy_translateZ = yellowEnemy_position.z - 0.5f;

    yellowEnemy_angularStepOY = atan2(yellowEnemy_forward.x, yellowEnemy_forward.z) - atan2(0, -1);

    //for (int i = 0; i < 40; i++)
    //    cout << i << " " << directions[i] << "\n";

    //enemy1Distance = 2.5f;
    //enemy1Distance = ((float)(rand() % 15 + 5)) / 10.0f;
    //enemy2Distance = ((float)(rand() % 5 + 5)) / 10.0f;

    //cout << enemy1Distance << " " << enemy2Distance << "\n";

    //glm::vec3 up = glm::vec3(0, 1, 0);

    //for (int i = 0; i < 40; i++)
    //{
    //    glm::vec3 p = glm::cross(directions[i], up);
    //    glm::vec3 r = roadPoints[i] + enemy1Distance * p;
    //    glm::vec3 b = roadPoints[i] - enemy2Distance * p;
    //    enemy1Points.push_back(r);
    //    enemy2Points.push_back(b);
    //}
    // ultimul punct



    //for (int i = 0; i < 40; i++)
        //cout << i << ": " << enemy1Points[i] << "\n";

    Mesh* road = obj3D::GenerateCompleteRoad("road", roadPoints, roadPointCount, glm::vec3(0.2f, 0.2f, 0.2f));
    AddMeshToList(road);

    Mesh* car = obj3D::CreateCuboid("car", position, 0.5f, 0.5f, 1.0f, glm::vec3(0, 1, 1));
    AddMeshToList(car);

    Mesh* purpleEnemy = obj3D::CreateCuboid("purpleEnemy", glm::vec3(0, 0.15f, 0), 0.5f, 0.5f, 1.0f, glm::vec3(0.73f, 0, 0.96f));
    AddMeshToList(purpleEnemy);

    Mesh* yellowEnemy = obj3D::CreateCuboid("yellowEnemy", glm::vec3(0, 0.15f, 0), 0.5f, 0.5f, 1.0f, glm::vec3(0.94f, 0.94f, 0));
    AddMeshToList(yellowEnemy);
}


Mesh* Tema2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices)
{
    unsigned int VAO = 0;
    // Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data.

    // TODO(student): If you look closely in the `Init()` and `Update()`
    // functions, you will see that we have three objects which we load
    // and use in three different ways:
    // - LoadMesh   + LabShader (this lab's shader)
    // - CreateMesh + VertexNormal (this shader is already implemented)
    // - CreateMesh + LabShader (this lab's shader)
    // To get an idea about how they're different from one another, do the
    // following experiments. What happens if you switch the color pipe and
    // normal pipe in this function (but not in the shader)? Now, what happens
    // if you do the same thing in the shader (but not in this function)?
    // Finally, what happens if you do the same thing in both places? Why?

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3))); // citeste dupa 3 float-uri, 3 * 8 = 24 bytes

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3))); // citeste dupa 6 float-uri

    //// Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2))); // citeste dupa 8 float-uri
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    return meshes[name];
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::RenderScene(float deltaTimeSeconds) {
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh(meshes["myCube"], shaders["LabShader"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh(meshes["green_plane"], shaders["LabShader"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh(meshes["horizon_top"], shaders["LabShader"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh(meshes["horizon_back"], shaders["LabShader"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh(meshes["horizon_right"], shaders["LabShader"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh(meshes["horizon_front"], shaders["LabShader"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh(meshes["horizon_left"], shaders["LabShader"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh(meshes["road"], shaders["LabShader"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transf3D::Translate(translateX, 0, translateZ);
        modelMatrix *= transf3D::RotateOY(angularStepOY);
        RenderSimpleMesh(meshes["car"], shaders["LabShader"], modelMatrix);
    }

    {
        if (initialTime >= 2.5f)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transf3D::Translate(purpleEnemy_translateX, 0, purpleEnemy_translateZ);
            modelMatrix *= transf3D::Translate(cx, 0, cz);
            modelMatrix *= transf3D::RotateOY(purpleEnemy_angularStepOY);
            modelMatrix *= transf3D::Translate(-cx, 0, -cz);
            RenderSimpleMesh(meshes["purpleEnemy"], shaders["LabShader"], modelMatrix);
        }
    }

    {
        if (initialTime >= 2.5f)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transf3D::Translate(yellowEnemy_translateX, 0, yellowEnemy_translateZ);
            modelMatrix *= transf3D::Translate(cx, 0, cz);
            modelMatrix *= transf3D::RotateOY(yellowEnemy_angularStepOY);
            modelMatrix *= transf3D::Translate(-cx, 0, -cz);
            RenderSimpleMesh(meshes["yellowEnemy"], shaders["LabShader"], modelMatrix);
        }
    }
}

//...............//

void Tema2::RenderScene2(float deltaTimeSeconds) {
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh2(meshes["myCube"], shaders["LabShader2"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh2(meshes["green_plane"], shaders["LabShader2"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh2(meshes["horizon_top"], shaders["LabShader2"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh2(meshes["horizon_back"], shaders["LabShader2"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh2(meshes["horizon_right"], shaders["LabShader2"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh2(meshes["horizon_front"], shaders["LabShader2"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh2(meshes["horizon_left"], shaders["LabShader2"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh2(meshes["road"], shaders["LabShader2"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transf3D::Translate(translateX, 0, translateZ);
        modelMatrix *= transf3D::RotateOY(angularStepOY);
        RenderSimpleMesh2(meshes["car"], shaders["LabShader2"], modelMatrix);
    }

    {
        if (initialTime >= 2.5f)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transf3D::Translate(purpleEnemy_translateX, 0, purpleEnemy_translateZ);
            modelMatrix *= transf3D::Translate(cx, 0, cz);
            modelMatrix *= transf3D::RotateOY(purpleEnemy_angularStepOY);
            modelMatrix *= transf3D::Translate(-cx, 0, -cz);
            RenderSimpleMesh2(meshes["purpleEnemy"], shaders["LabShader"], modelMatrix);
        }
    }

    {
        if (initialTime >= 2.5f)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transf3D::Translate(yellowEnemy_translateX, 0, yellowEnemy_translateZ);
            modelMatrix *= transf3D::Translate(cx, 0, cz);
            modelMatrix *= transf3D::RotateOY(yellowEnemy_angularStepOY);
            modelMatrix *= transf3D::Translate(-cx, 0, -cz);
            RenderSimpleMesh2(meshes["yellowEnemy"], shaders["LabShader"], modelMatrix);
        }
    }
}



void Tema2::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);

    float enemyMovementSpeed = 5.0f;

    initialTime += deltaTimeSeconds;

    if (initialTime >= 2.5f)
    {
        if ((glm::abs(purpleEnemy_translateX + 0.25f - purpleEnemyPoints[purpleEnemy_counter].x) < 0.1f) && (glm::abs(purpleEnemy_translateZ + 0.5f - purpleEnemyPoints[purpleEnemy_counter].z) < 0.1f))
        {
            purpleEnemy_translateX = purpleEnemyPoints[purpleEnemy_counter].x - 0.25f;
            purpleEnemy_translateZ = purpleEnemyPoints[purpleEnemy_counter].z - 0.5f;

            purpleEnemy_forward = purpleEnemyDirections[purpleEnemy_counter];

            purpleEnemy_angularStepOY = atan2(purpleEnemy_forward.x, purpleEnemy_forward.z) - atan2(0, -1);

            if (purpleEnemy_angularStepOY < 0)
                purpleEnemy_angularStepOY += 2 * M_PI;

            if (purpleEnemy_counter == 39)
                purpleEnemy_counter = 0;
            else
                purpleEnemy_counter++;
        }
        else
        {
            purpleEnemy_translateX += glm::normalize(purpleEnemy_forward).x * enemyMovementSpeed * deltaTimeSeconds;
            purpleEnemy_translateZ += glm::normalize(purpleEnemy_forward).z * enemyMovementSpeed * deltaTimeSeconds;
        }

        if ((glm::abs(yellowEnemy_translateX + 0.25f - yellowEnemyPoints[yellowEnemy_counter].x) < 0.1f) && (glm::abs(yellowEnemy_translateZ + 0.5f - yellowEnemyPoints[yellowEnemy_counter].z) < 0.1f))
        {
            yellowEnemy_translateX = yellowEnemyPoints[yellowEnemy_counter].x - 0.25f;
            yellowEnemy_translateZ = yellowEnemyPoints[yellowEnemy_counter].z - 0.5f;

            if (yellowEnemy_counter == 0)
                yellowEnemy_forward = -yellowEnemyDirections[39];
            else
                yellowEnemy_forward = -yellowEnemyDirections[yellowEnemy_counter - 1];

            yellowEnemy_angularStepOY = atan2(yellowEnemy_forward.x, yellowEnemy_forward.z) - atan2(0, -1);

            if (yellowEnemy_angularStepOY < 0)
                yellowEnemy_angularStepOY += 2 * M_PI;

            if (yellowEnemy_counter == 0)
                yellowEnemy_counter = 39;
            else
                yellowEnemy_counter--;
        }
        else
        {
            yellowEnemy_translateX += glm::normalize(yellowEnemy_forward).x * enemyMovementSpeed * deltaTimeSeconds;
            yellowEnemy_translateZ += glm::normalize(yellowEnemy_forward).z * enemyMovementSpeed * deltaTimeSeconds;
        }
    }

    RenderScene(deltaTimeSeconds);

    //DrawCoordinateSystem();

    //projectionMatrix = glm::ortho(left, right, bottom, up, zNear, zFar);
    //camera->Set(glm::vec3(0, 5, 0.1f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

  
    //camera->position = glm::vec3(transf3D::Translate(0, 10, 6) * glm::vec4(camera->position, 1));
    //camera->RotateThirdPerson_OX(-120);
    //projectionMatrix = glm::ortho(left, right, bottom, up, zNear, zFar);

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    // TODO(student): render the scene again, in the new viewport
    RenderScene2(deltaTimeSeconds);

    // camera->RotateThirdPerson_OX(120);
    //projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, zNear, zFar);
    //DrawCoordinateSystem();
}


void Tema2::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // TODO(student): Get shader location for uniform mat4 "Model"
    int location1 = glGetUniformLocation(shader->program, "Model");
    //int location = glGetUniformLocation(shader->program, "Nume1");
    //glUniform1f(location, 3.12312f);
    //glUniform1i(location, 3); // daca vreau sa trimit un int
    //glUniform3f(location, /* 3 float-uri */);

    // TODO(student): Set shader uniform "Model" to modelMatrix

    // TODO(student): Get shader location for uniform mat4 "View"
    int location2 = glGetUniformLocation(shader->program, "View");

    // TODO(student): Set shader uniform "View" to viewMatrix
    //glm::mat4 viewMatrix = camera->GetViewMatrix();
    //glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();

    // TODO(student): Get shader location for uniform mat4 "Projection"
    int location3 = glGetUniformLocation(shader->program, "Projection");

    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, zNear, zFar);


    glUniformMatrix4fv(location1, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(location2, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(location3, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    //glUniformMatrix4fv(location4, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    //glUniformMatrix4fv(location5, 1, GL_FALSE, glm::value_ptr(miniCamera->GetViewMatrix()));
    //glUniformMatrix4fv(location6, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);


    //..................................................//

    
}

void Tema2::RenderSimpleMesh2(Mesh* mesh, Shader* shader2, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader2 || !shader2->GetProgramID())
        return;

    glUseProgram(shader2->program);

    // TODO(student): Get shader location for uniform mat4 "Model"
    int location4 = glGetUniformLocation(shader2->program, "Model");
    //int location = glGetUniformLocation(shader->program, "Nume1");
    //glUniform1f(location, 3.12312f);
    //glUniform1i(location, 3); // daca vreau sa trimit un int
    //glUniform3f(location, /* 3 float-uri */);

    // TODO(student): Set shader uniform "Model" to modelMatrix

    // TODO(student): Get shader location for uniform mat4 "View"
    int location5 = glGetUniformLocation(shader2->program, "View");

    // TODO(student): Set shader uniform "View" to viewMatrix
    //glm::mat4 viewMatrix = camera->GetViewMatrix();
    //glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();

    // TODO(student): Get shader location for uniform mat4 "Projection"
    int location6 = glGetUniformLocation(shader2->program, "Projection");

    projectionMatrix = glm::ortho(left, right, bottom, up, zNear, zFar);


    glUniformMatrix4fv(location4, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(location5, 1, GL_FALSE, glm::value_ptr(miniCamera->GetViewMatrix()));
    glUniformMatrix4fv(location6, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    //glUniformMatrix4fv(location4, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    //glUniformMatrix4fv(location5, 1, GL_FALSE, glm::value_ptr(miniCamera->GetViewMatrix()));
    //glUniformMatrix4fv(location6, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    // Add key press event
    float movementSpeed = 7.5f;
    float rotationSpeed = 1.0f;

    timeFreeze += deltaTime;

    if (checkCollision(glm::vec3(translateX, 0.4f, translateZ), glm::vec3(purpleEnemy_translateX + 0.25f, 0.4f, purpleEnemy_translateZ + 0.5f), 0.5f, 0.5f) ||
        checkCollision(glm::vec3(translateX, 0.4f, translateZ), glm::vec3(yellowEnemy_translateX + 0.25f, 0.4f, yellowEnemy_translateZ + 0.5f), 0.5f, 0.5f))
        timeFreeze = 0;

    if (timeFreeze >= 0.0625f)
    {
        if (window->KeyHold(GLFW_KEY_S) && checkAll(roadPoints, roadPointCount, glm::vec3(translateX - glm::normalize(forward).x * movementSpeed * deltaTime, 0.13f, translateZ - glm::normalize(forward).z * movementSpeed * deltaTime)))
        {
            translateX -= glm::normalize(forward).x * movementSpeed * deltaTime;
            translateZ -= glm::normalize(forward).z * movementSpeed * deltaTime;
            camera->MoveForward(-movementSpeed * deltaTime);

            miniCamera->position = glm::vec3(translateX, 15, translateZ);
        }
        if (window->KeyHold(GLFW_KEY_W) && checkAll(roadPoints, roadPointCount, glm::vec3(translateX + glm::normalize(forward).x * movementSpeed * deltaTime, 0.13f, translateZ + glm::normalize(forward).z * movementSpeed * deltaTime)))
        {
            translateX += glm::normalize(forward).x * movementSpeed * deltaTime;
                translateZ += glm::normalize(forward).z * movementSpeed * deltaTime;
                camera->MoveForward(movementSpeed* deltaTime); // nu merge bn nici S

                //miniCamera->MoveForward(movementSpeed * deltaTime); // nu merge bn nici S
                miniCamera->position = glm::vec3(translateX, 15, translateZ);
        }
        if (window->KeyHold(GLFW_KEY_A))
        {
            angularStepOY += rotationSpeed * deltaTime;
            forward = glm::normalize(glm::rotate(glm::mat4(1.0f), rotationSpeed * deltaTime, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1));
            camera->RotateThirdPerson_OY(rotationSpeed * deltaTime);
        }


        if (window->KeyHold(GLFW_KEY_D))
        {
            angularStepOY -= rotationSpeed * deltaTime;
            forward = glm::normalize(glm::rotate(glm::mat4(1.0f), -rotationSpeed * deltaTime, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1));
            //rightV = glm::normalize(glm::rotate(glm::mat4(1.0f), -rotationSpeed * deltaTime, glm::vec3(0, 1, 0)) * glm::vec4(rightV, 1));
            camera->RotateThirdPerson_OY(-rotationSpeed * deltaTime);
            //miniCamera->forward = glm::normalize(forward);
            //cout << "forward: " << forward << "\n";
            //cout << "camera->forward: " << camera->forward << "\n";
            //cout << "miniCamera->forward: " << miniCamera->forward << "\n";
            //miniCamera->forward = forward;
            //miniCamera->right = rightV;
            //cout << camera->forward << "\n";
        }
    }
}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
