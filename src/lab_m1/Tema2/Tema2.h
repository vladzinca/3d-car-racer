#pragma once

#include <vector>
#include <string>

#include "components/simple_scene.h"
#include "lab_m1/Tema2/obj3D.h"
#include "lab_m1/Tema2/transf3D.h"
#include "lab_m1/Tema2/hw_camera.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        Tema2();
        ~Tema2();

        void Init() override;

        Mesh *CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices);

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix);
        void RenderSimpleMeshMini(Mesh* mesh, Shader* shader2, const glm::mat4& modelMatrix);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void RenderScene();
        void RenderSceneMini();

    protected:
        implement::Camera* camera;
        implement::Camera* miniCamera;
        glm::vec3 cameraPosition, miniCameraPosition;

        float translateX, translateZ, angularStepOY;
        glm::vec3 position, forward;
        float carWidth, carHeight, carLength;
        float cx, cy, cz;
        float initialTime, timeFreeze;
        int tmp;

        float fov, zNear, zFar, left, right, bottom, up;
        glm::mat4 projectionMatrix;
        ViewportArea miniViewportArea;

        int roadPointCount;
        std::vector<glm::vec3> roadPoints;

        float redDistance, blueDistance;
        float purpleEnemyDistance, yellowEnemyDistance;
        float treeRedDistance, treeBlueDistance;

        std::vector<glm::vec3> directions, purpleEnemyPoints, yellowEnemyPoints, treeCoordinates;
        std::vector<glm::vec3> purpleEnemyDirections, yellowEnemyDirections;

        int purpleEnemy_counter;
        glm::vec3 purpleEnemy_position, purpleEnemy_forward;
        float purpleEnemy_translateX, purpleEnemy_translateZ, purpleEnemy_angularStepOY;
        
        int yellowEnemy_counter;
        glm::vec3 yellowEnemy_position, yellowEnemy_forward;
        float yellowEnemy_translateX, yellowEnemy_translateZ, yellowEnemy_angularStepOY;

    };
}
