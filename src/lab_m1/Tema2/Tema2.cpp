#include "lab_m1/Tema2/tema2.h"

using namespace std;
using namespace m1;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
    camera = new implement::Camera();
    camera->Set(glm::vec3(0, 2, 2), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    miniCamera = new implement::Camera();
    miniCamera->Set(glm::vec3(0, 15, 0.1f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    cameraPosition = glm::vec3(0, 2, 2);
    miniCameraPosition = glm::vec3(0, 15, 0.1f);

    translateX = 0;
    translateZ = 0;
    angularStepOY = 0;

    position = glm::vec3(-0.25f, 0.15f, -0.5f);
    forward = glm::vec3(0, 0, -1);

    carWidth = 0.5f;
    carHeight = 0.5f;
    carLength = 1;

    cx = carWidth / 2.0f;
    cy = carHeight / 2.0f;
    cz = carLength / 2.0f;

    initialTime = 0;
    timeFreeze = 0;
    tmp = 0;

    fov = 60.0f;
    zNear = 0.01f;
    zFar = 200.0f;
    left = -15.0f;
    right = 15.0f;
    bottom = -7.5f;
    up = 7.5f;

    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, (int)(resolution.x / 4.0f), (int)(resolution.y / 4.0f));

    {
        Shader *shader = new Shader("HWShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;

        Shader* miniShader = new Shader("MiniHWShader");
        miniShader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShaderMini.glsl"), GL_VERTEX_SHADER);
        miniShader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShaderMini.glsl"), GL_FRAGMENT_SHADER);
        miniShader->CreateAndLink();
        shaders[miniShader->GetName()] = miniShader;
    }

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

    redDistance = 2.5f;
    blueDistance = 1.5f;

    purpleEnemyDistance = ((float)(rand() % 15 + 5)) / 10.0f;
    yellowEnemyDistance = ((float)(rand() % 5 + 5)) / 10.0f;

    treeRedDistance = redDistance * 2.0f;
    treeBlueDistance = blueDistance * 2.0f;
    
    for (int i = 0; i < roadPointCount - 1; i++)
    {
        tmp = i + 1;
        glm::vec3 d = glm::normalize(roadPoints[tmp] - roadPoints[i]);
        directions.push_back(d);

        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 p = glm::cross(d, up);

        glm::vec3 r = roadPoints[i] + purpleEnemyDistance * p;
        glm::vec3 b = roadPoints[i] - yellowEnemyDistance * p;
        glm::vec3 tr = roadPoints[i] + treeRedDistance * p;
        glm::vec3 tb = roadPoints[i] - treeBlueDistance * p;
        tr.y = 0;
        tb.y = 0;

        purpleEnemyPoints.push_back(r);
        yellowEnemyPoints.push_back(b);
        treeCoordinates.push_back(tr);
        treeCoordinates.push_back(tb);
    }

    tmp = roadPointCount - 1;
    glm::vec3 d = glm::normalize(roadPoints[0] - roadPoints[tmp]);
    directions.push_back(d);

    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 p = glm::cross(d, up);

    glm::vec3 r = roadPoints[tmp] + purpleEnemyDistance * p;
    glm::vec3 b = roadPoints[tmp] - yellowEnemyDistance * p;
    glm::vec3 tr = roadPoints[tmp] + treeRedDistance * p;
    glm::vec3 tb = roadPoints[tmp] - treeBlueDistance * p;
    tr.y = 0;
    tb.y = 0;

    purpleEnemyPoints.push_back(r);
    yellowEnemyPoints.push_back(b);
    treeCoordinates.push_back(tr);
    treeCoordinates.push_back(tb);

    for (int i = 0; i < roadPointCount - 1; i++)
    {
        tmp = i + 1;
        purpleEnemyDirections.push_back(glm::normalize(purpleEnemyPoints[tmp] - purpleEnemyPoints[i]));
        yellowEnemyDirections.push_back(glm::normalize(yellowEnemyPoints[tmp] - yellowEnemyPoints[i]));
    }

    tmp = roadPointCount - 1;
    purpleEnemyDirections.push_back(glm::normalize(purpleEnemyPoints[0] - purpleEnemyPoints[tmp]));
    yellowEnemyDirections.push_back(glm::normalize(yellowEnemyPoints[0] - yellowEnemyPoints[tmp]));

    purpleEnemy_counter = 11;
    purpleEnemy_position = purpleEnemyPoints[10];
    purpleEnemy_forward = purpleEnemyDirections[10];

    purpleEnemy_translateX = purpleEnemy_position.x - 0.25f;
    purpleEnemy_translateZ = purpleEnemy_position.z - 0.5f;
    purpleEnemy_angularStepOY = (float)(atan2(purpleEnemy_forward.x, purpleEnemy_forward.z) - atan2(0, -1));

    yellowEnemy_counter = 11;
    yellowEnemy_forward = -yellowEnemyDirections[11];
    yellowEnemy_position = yellowEnemyPoints[12];

    yellowEnemy_translateX = yellowEnemy_position.x - 0.25f;
    yellowEnemy_translateZ = yellowEnemy_position.z - 0.5f;
    yellowEnemy_angularStepOY = (float)(atan2(yellowEnemy_forward.x, yellowEnemy_forward.z) - atan2(0, -1));

    Mesh* green_plane = obj3D::CreatePlane("green_plane", glm::vec3(-64, 0.05f, -64), 128, 128, glm::vec3(0.5f, 0.8f, 0.3f));
    AddMeshToList(green_plane);

    Mesh* road = obj3D::CreateRoad("road", roadPoints, roadPointCount, redDistance, blueDistance, glm::vec3(0.2f, 0.2f, 0.2f));
    AddMeshToList(road);

    for (int i = 0; i < 80; i++)
    {
        Mesh* tree = obj3D::CreateTree("tree" + std::to_string(i), treeCoordinates[i], 0.5f, 1, 2, glm::vec3(0.44f, 0.35f, 0.28f), glm::vec3(0.35f, 0.5f, 0.28f));
        AddMeshToList(tree);
    }

    Mesh* car = obj3D::CreateCar("car", position, carWidth, carHeight, carLength, glm::vec3(0, 1, 1));
    AddMeshToList(car);

    Mesh* purpleEnemy = obj3D::CreateCar("purpleEnemy", glm::vec3(0, 0.15f, 0), carWidth, carHeight, carLength, glm::vec3(0.73f, 0, 0.96f));
    AddMeshToList(purpleEnemy);

    Mesh* yellowEnemy = obj3D::CreateCar("yellowEnemy", glm::vec3(0, 0.15f, 0), carWidth, carHeight, carLength, glm::vec3(0.94f, 0.94f, 0));
    AddMeshToList(yellowEnemy);
}

Mesh* Tema2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices)
{
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

    glBindVertexArray(0);

    CheckOpenGLError();

    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    return meshes[name];
}

void Tema2::FrameStart()
{
    glClearColor(0.5f, 0.8f, 0.9f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::RenderScene() {
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh(meshes["green_plane"], shaders["HWShader"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMesh(meshes["road"], shaders["HWShader"], modelMatrix);
    }

    {
        for (int i = 0; i < 80; i++)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            RenderSimpleMesh(meshes["tree" + std::to_string(i)], shaders["HWShader"], modelMatrix);
        }
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transf3D::Translate(translateX, 0, translateZ);
        modelMatrix *= transf3D::RotateOY(angularStepOY);
        RenderSimpleMesh(meshes["car"], shaders["HWShader"], modelMatrix);
    }

    {
        if (initialTime >= 10.0f)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transf3D::Translate(purpleEnemy_translateX, 0, purpleEnemy_translateZ);
            modelMatrix *= transf3D::Translate(cx, 0, cz);
            modelMatrix *= transf3D::RotateOY(purpleEnemy_angularStepOY);
            modelMatrix *= transf3D::Translate(-cx, 0, -cz);
            RenderSimpleMesh(meshes["purpleEnemy"], shaders["HWShader"], modelMatrix);
        }
    }

    {
        if (initialTime >= 10.0f)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transf3D::Translate(yellowEnemy_translateX, 0, yellowEnemy_translateZ);
            modelMatrix *= transf3D::Translate(cx, 0, cz);
            modelMatrix *= transf3D::RotateOY(yellowEnemy_angularStepOY);
            modelMatrix *= transf3D::Translate(-cx, 0, -cz);
            RenderSimpleMesh(meshes["yellowEnemy"], shaders["HWShader"], modelMatrix);
        }
    }
}

void Tema2::RenderSceneMini() {
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMeshMini(meshes["green_plane"], shaders["MiniHWShader"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderSimpleMeshMini(meshes["road"], shaders["MiniHWShader"], modelMatrix);
    }

    {
        for (int i = 0; i < 80; i++)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            RenderSimpleMeshMini(meshes["tree" + std::to_string(i)], shaders["MiniHWShader"], modelMatrix);
        }
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transf3D::Translate(translateX, 0, translateZ);
        modelMatrix *= transf3D::RotateOY(angularStepOY);
        RenderSimpleMeshMini(meshes["car"], shaders["MiniHWShader"], modelMatrix);
    }

    {
        if (initialTime >= 10.0f)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transf3D::Translate(purpleEnemy_translateX, 0, purpleEnemy_translateZ);
            modelMatrix *= transf3D::Translate(cx, 0, cz);
            modelMatrix *= transf3D::RotateOY(purpleEnemy_angularStepOY);
            modelMatrix *= transf3D::Translate(-cx, 0, -cz);
            RenderSimpleMeshMini(meshes["purpleEnemy"], shaders["MiniHWShader"], modelMatrix);
        }
    }

    {
        if (initialTime >= 10.0f)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transf3D::Translate(yellowEnemy_translateX, 0, yellowEnemy_translateZ);
            modelMatrix *= transf3D::Translate(cx, 0, cz);
            modelMatrix *= transf3D::RotateOY(yellowEnemy_angularStepOY);
            modelMatrix *= transf3D::Translate(-cx, 0, -cz);
            RenderSimpleMeshMini(meshes["yellowEnemy"], shaders["MiniHWShader"], modelMatrix);
        }
    }
}

void Tema2::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);

    float enemyMovementSpeed = 5.0f;
    initialTime += deltaTimeSeconds;

    if (initialTime >= 10.0f)
    {
        if ((glm::abs(purpleEnemy_translateX + cx - purpleEnemyPoints[purpleEnemy_counter].x) < 0.1f) &&
            (glm::abs(purpleEnemy_translateZ + cz - purpleEnemyPoints[purpleEnemy_counter].z) < 0.1f))
        {
            purpleEnemy_translateX = purpleEnemyPoints[purpleEnemy_counter].x - cx;
            purpleEnemy_translateZ = purpleEnemyPoints[purpleEnemy_counter].z - cz;

            purpleEnemy_forward = purpleEnemyDirections[purpleEnemy_counter];

            purpleEnemy_angularStepOY = (float)(atan2(purpleEnemy_forward.x, purpleEnemy_forward.z) - atan2(0, -1));
            if (purpleEnemy_angularStepOY < 0)
                purpleEnemy_angularStepOY += (float)(2 * M_PI);

            if (purpleEnemy_counter == roadPointCount - 1)
                purpleEnemy_counter = 0;
            else
                purpleEnemy_counter++;
        }
        else
        {
            purpleEnemy_translateX += glm::normalize(purpleEnemy_forward).x * enemyMovementSpeed * deltaTimeSeconds;
            purpleEnemy_translateZ += glm::normalize(purpleEnemy_forward).z * enemyMovementSpeed * deltaTimeSeconds;
        }

        if ((glm::abs(yellowEnemy_translateX + cx - yellowEnemyPoints[yellowEnemy_counter].x) < 0.1f) &&
            (glm::abs(yellowEnemy_translateZ + cz - yellowEnemyPoints[yellowEnemy_counter].z) < 0.1f))
        {
            yellowEnemy_translateX = yellowEnemyPoints[yellowEnemy_counter].x - cx;
            yellowEnemy_translateZ = yellowEnemyPoints[yellowEnemy_counter].z - cz;

            if (yellowEnemy_counter == 0)
            {
                tmp = roadPointCount - 1;
                yellowEnemy_forward = -yellowEnemyDirections[tmp];
            }
            else
            {
                tmp = yellowEnemy_counter - 1;
                yellowEnemy_forward = -yellowEnemyDirections[tmp];
            }

            yellowEnemy_angularStepOY = (float)(atan2(yellowEnemy_forward.x, yellowEnemy_forward.z) - atan2(0, -1));
            if (yellowEnemy_angularStepOY < 0)
                yellowEnemy_angularStepOY += (float)(2 * M_PI);

            if (yellowEnemy_counter == 0)
                yellowEnemy_counter = roadPointCount - 1;
            else
                yellowEnemy_counter--;
        }
        else
        {
            yellowEnemy_translateX += glm::normalize(yellowEnemy_forward).x * enemyMovementSpeed * deltaTimeSeconds;
            yellowEnemy_translateZ += glm::normalize(yellowEnemy_forward).z * enemyMovementSpeed * deltaTimeSeconds;
        }
    }

    RenderScene();

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    RenderSceneMini();
}


void Tema2::FrameEnd()
{
}


void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    glUseProgram(shader->program);

    int location1 = glGetUniformLocation(shader->program, "Model");
    int location2 = glGetUniformLocation(shader->program, "View");
    int location3 = glGetUniformLocation(shader->program, "Projection");

    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, zNear, zFar);

    glUniformMatrix4fv(location1, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(location2, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(location3, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema2::RenderSimpleMeshMini(Mesh* mesh, Shader* miniShader, const glm::mat4& modelMatrix)
{
    if (!mesh || !miniShader || !miniShader->GetProgramID())
        return;

    glUseProgram(miniShader->program);

    int location1 = glGetUniformLocation(miniShader->program, "Model");
    int location2 = glGetUniformLocation(miniShader->program, "View");
    int location3 = glGetUniformLocation(miniShader->program, "Projection");

    projectionMatrix = glm::ortho(left, right, bottom, up, zNear, zFar);

    glUniformMatrix4fv(location1, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(location2, 1, GL_FALSE, glm::value_ptr(miniCamera->GetViewMatrix()));
    glUniformMatrix4fv(location3, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float movementSpeed = 7.5f;
    float rotationSpeed = 1.0f;
    timeFreeze += deltaTime;

    if (obj3D::CheckCarCollision(glm::vec3(translateX, 0.4f, translateZ),
                              glm::vec3(purpleEnemy_translateX + cx, 0.4f, purpleEnemy_translateZ + cz), cz, cz) ||
        obj3D::CheckCarCollision(glm::vec3(translateX, 0.4f, translateZ),
                              glm::vec3(yellowEnemy_translateX + cx, 0.4f, yellowEnemy_translateZ + cz), cz, cz))
        timeFreeze = 0;

    if (timeFreeze >= 0.0625f)
    {
        if (window->KeyHold(GLFW_KEY_S) &&
            obj3D::CheckAllTriangles(roadPoints, roadPointCount,
                            glm::vec3(translateX - glm::normalize(forward).x * movementSpeed * deltaTime, 0.13f,
                                      translateZ - glm::normalize(forward).z * movementSpeed * deltaTime)))
        {
            translateX -= glm::normalize(forward).x * movementSpeed * deltaTime;
            translateZ -= glm::normalize(forward).z * movementSpeed * deltaTime;

            camera->MoveForward(-movementSpeed * deltaTime);
            miniCamera->position = glm::vec3(translateX, 15, translateZ);
        }

        if (window->KeyHold(GLFW_KEY_W) &&
            obj3D::CheckAllTriangles(roadPoints, roadPointCount,
                            glm::vec3(translateX + glm::normalize(forward).x * movementSpeed * deltaTime, 0.13f,
                                      translateZ + glm::normalize(forward).z * movementSpeed * deltaTime)))
        {
            translateX += glm::normalize(forward).x * movementSpeed * deltaTime;
            translateZ += glm::normalize(forward).z * movementSpeed * deltaTime;

            camera->MoveForward(movementSpeed* deltaTime);
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
            camera->RotateThirdPerson_OY(-rotationSpeed * deltaTime);
        }
    }
}

void Tema2::OnKeyPress(int key, int mods)
{
}

void Tema2::OnKeyRelease(int key, int mods)
{
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
