#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        float cx, cy;
        glm::mat3 modelMatrix, tmpModelMatrix, staticModelMatrix;
        float translateX, translateY;
        float scoreScaleX, scoreScaleY;
        float leftAngularStep, rightAngularStep;

        float rectangleWidth, rectangleHeight;
        float headPositionWidth, headPositionHeight;

        int randomAngle;
        float randomRadianAngle;

        float timeElapsed;

        int duckCount, escapedDuckCount, killedDuckCount;
        float speed, initialSpeed, speedCoefficient;

        float coordinatesX, coordinatesY;

        float headX, headY;

        bool isFirstBird, birdEscaped, reachedHeaven, isHit, reachedFloor, debugMode;

        int lifeCount, bulletCount, score;

        bool gameOver, displayOnlyOnce;

        float trueMouseX, trueMouseY;
    };
}   // namespace m1
