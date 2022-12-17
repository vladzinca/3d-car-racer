#pragma once

#include <vector>

#include "components/simple_scene.h"
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
        void RenderSimpleMesh2(Mesh* mesh, Shader* shader2, const glm::mat4& modelMatrix);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void RenderScene();

        void RenderScene2();

        float computeArea(glm::vec3 A, glm::vec3 B, glm::vec3 C);
        int checkPoint(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 P);
        int checkAll(std::vector<glm::vec3> points, int pointCount, glm::vec3 P);

        float translateX, translateZ;
        float angularStepOY;

        glm::vec3 enemy1_position;
        float enemy1_translateX, enemy1_translateZ;
        float enemy1_angularStepOY;

        glm::vec3 enemy1_forward;
        int enemy1_counter;
        
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 rightV;

        std::vector<glm::vec3> directions;
        float enemy1Distance, enemy2Distance;
        std::vector<glm::vec3> enemy1Points;
        std::vector<glm::vec3> enemy2Points;

    protected:
        implement::Camera* camera;
        implement::Camera* miniCamera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        float fov, zNear, zFar;
        float left, right, bottom, up;
        ViewportArea miniViewportArea;
        glm::vec3 cameraPosition;
        glm::vec3 miniCameraPosition;
        int flag, flag2;

        std::vector<glm::vec3> roadPoints;
        int roadPointCount;
    };
}   // namespace m1
