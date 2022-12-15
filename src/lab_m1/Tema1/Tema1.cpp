#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transf2D.h"
#include "lab_m1/Tema1/obj2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    /* Initialize size of duck*/
    rectangleWidth = 280;
    rectangleHeight = 230;
    /* Initialize center of head circle coordinates */
    headPositionWidth = 210;
    headPositionHeight = 120;

    cx = corner.x + rectangleWidth / 2.0f;
    cy = corner.y + rectangleHeight / 2.0f;

    /* Initialize first direction angle */
    randomAngle = transf2D::getRandomAngle();
    randomRadianAngle = transf2D::getRadiansFromAngle(randomAngle);

    /* Initialize time since duck spawn */
    timeElapsed = 0;

    /* Initialize number of ducks (when 5, reset to 0) */
    duckCount = 0;
    escapedDuckCount = 0;
    killedDuckCount = 0;
    /* Initialize speed and speed coefficient used to increase it */
    speed = 250;
    initialSpeed = speed;
    speedCoefficient = 1;

    /* Initialize coordinates of duck's center with random place inside the grass */
    coordinatesX = cx + (resolution.x - rectangleWidth) * transf2D::getStartingCoordinate();
    coordinatesY = cy;

    /* Initialize coordinates of head's center */
    headX = 0;
    headY = 0;

    /* Initialize translation coordinates (left bottom corner of duck) */
    translateX = 0;
    translateY = 0;

    /* Initialize scale factors for scoreboard */
    scoreScaleX = 1;
    scoreScaleY = 1;

    /* Initialize rotation angles for wings */
    leftAngularStep = 0;
    rightAngularStep = 0;

    /* Initialize event flags */
    isFirstBird = true;
    birdEscaped = false;
    reachedHeaven = false;
    isHit = false;
    reachedFloor = false;
    debugMode = false;

    /* Initialize gameplay indicators */
    lifeCount = 3;
    bulletCount = 3;
    score = 0;

    /* Initialize final stage flags */
    gameOver = false;
    displayOnlyOnce = true;

    /* Create meshes to be displayed */
    Mesh* grass = obj2D::CreateRectangle("grass", corner, (float)resolution.x, 230, glm::vec3(0, 0.6f, 0.09f), true);
    AddMeshToList(grass);


    Mesh* firstHeart = obj2D::CreateCircle("firstHeart", corner + glm::vec3(30, 690, 0), 20, 64, glm::vec3(0.93f, 0.13f, 0.15f), true);
    AddMeshToList(firstHeart);

    Mesh* secondHeart = obj2D::CreateCircle("secondHeart", corner + glm::vec3(80, 690, 0), 20, 64, glm::vec3(0.93f, 0.13f, 0.15f), true);
    AddMeshToList(secondHeart);

    Mesh* thirdHeart = obj2D::CreateCircle("thirdHeart", corner + glm::vec3(130, 690, 0), 20, 64, glm::vec3(0.93f, 0.13f, 0.15f), true);
    AddMeshToList(thirdHeart);


    Mesh* firstBullet = obj2D::CreateRectangle("firstBullet", corner + glm::vec3(15, 630, 0), 15, 30, glm::vec3(0.15f, 0.26f, 0.15f), true);
    AddMeshToList(firstBullet);

    Mesh* secondBullet = obj2D::CreateRectangle("secondBullet", corner + glm::vec3(45, 630, 0), 15, 30, glm::vec3(0.15f, 0.26f, 0.15f), true);
    AddMeshToList(secondBullet);

    Mesh* thirdBullet = obj2D::CreateRectangle("thirdBullet", corner + glm::vec3(75, 630, 0), 15, 30, glm::vec3(0.15f, 0.26f, 0.15f), true);
    AddMeshToList(thirdBullet);


    Mesh* wireframeScore = obj2D::CreateRectangle("wireframeScore", corner + glm::vec3(1010, 640, 0), 250, 60, glm::vec3(1, 1, 1), false);
    AddMeshToList(wireframeScore);

    Mesh* solidScore = obj2D::CreateRectangle("solidScore", corner, 2.5f, 60, glm::vec3(0, 0, 0.67f), true);
    AddMeshToList(solidScore);


    Mesh* hitbox = obj2D::CreateRectangle("hitbox", corner, 280, 230, glm::vec3(1, 0.5f, 1), false);
    AddMeshToList(hitbox);

    Mesh* bodyCenter = obj2D::CreateSquare("bodyCenter", corner + glm::vec3(140, 115, 0), 2, glm::vec3(1, 0.5f, 1), true);
    AddMeshToList(bodyCenter);

    Mesh* headCenter = obj2D::CreateSquare("headCenter", corner + glm::vec3(210, 120, 0), 2, glm::vec3(1, 0.5f, 1), true);
    AddMeshToList(headCenter);

    /* Generalize head coordinates as seen above */
    Mesh* head = obj2D::CreateCircle("head", corner + glm::vec3(headPositionWidth, headPositionHeight, 0), 40, 64, glm::vec3(0.19f, 0.34f, 0.22f), true);
    AddMeshToList(head);

    Mesh* body = obj2D::CreateTriangle("body", corner + glm::vec3(0, 70, 0), corner + glm::vec3(0, 160, 0), corner + glm::vec3(210, 115.2f, 0),
                                        glm::vec3(0.35f, 0.23f, 0.15f), true);
    AddMeshToList(body);

    Mesh* beak = obj2D::CreateTriangle("beak", corner + glm::vec3(236, 98, 0), corner + glm::vec3(236, 116, 0), corner + glm::vec3(280, 104, 0),
                                        glm::vec3(0.91f, 0.8f, 0.23f), true);
    AddMeshToList(beak);


    Mesh* leftArm = obj2D::CreateTriangle("leftArm", corner + glm::vec3(70, 130, 0), corner + glm::vec3(130, 130, 0), corner + glm::vec3(100, 230, 0),
                                        glm::vec3(0.35f, 0.23f, 0.15f), true);
    AddMeshToList(leftArm);

    Mesh* rightArm = obj2D::CreateTriangle("rightArm", corner + glm::vec3(70, 100, 0), corner + glm::vec3(130, 100, 0), corner + glm::vec3(100, 0, 0),
                                        glm::vec3(0.35f, 0.23f, 0.15f), true);
    AddMeshToList(rightArm);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0.5f, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    if (!debugMode)
    {
        /* Display static meshes on screen */
        staticModelMatrix = glm::mat3(1);
        if (!gameOver)
            RenderMesh2D(meshes["grass"], shaders["VertexColor"], staticModelMatrix);

        if (lifeCount >= 1)
            RenderMesh2D(meshes["firstHeart"], shaders["VertexColor"], staticModelMatrix);

        if (lifeCount >= 2)
            RenderMesh2D(meshes["secondHeart"], shaders["VertexColor"], staticModelMatrix);

        if (lifeCount == 3)
            RenderMesh2D(meshes["thirdHeart"], shaders["VertexColor"], staticModelMatrix);

        if (bulletCount >= 1)
            RenderMesh2D(meshes["firstBullet"], shaders["VertexColor"], staticModelMatrix);

        if (bulletCount >= 2)
            RenderMesh2D(meshes["secondBullet"], shaders["VertexColor"], staticModelMatrix);

        if (bulletCount >= 3)
            RenderMesh2D(meshes["thirdBullet"], shaders["VertexColor"], staticModelMatrix);

        RenderMesh2D(meshes["wireframeScore"], shaders["VertexColor"], staticModelMatrix);

        staticModelMatrix *= transf2D::Translate(1010, 640);

        scoreScaleX = (float)score;
        staticModelMatrix *= transf2D::Scale(scoreScaleX, scoreScaleY);

        RenderMesh2D(meshes["solidScore"], shaders["VertexColor"], staticModelMatrix);
    }

    /* Conditions for the game to cease */
    if (lifeCount == 0 || score == 100)
        gameOver = true;
    else
        gameOver = false;

    /* Display message in CLI */
    if (gameOver && displayOnlyOnce)
    {
        cout << "================================================\n";
        cout << "=              Duck Hunt Console               =\n";
        cout << "================================================\n";
        if (lifeCount == 0)
        {

            cout << "= Game over! (You ran out of lives)            =\n";
            if (score >= 10)
                cout << "= Your score was " << score << " / 100.                     =\n";
            else
                cout << "= Your score was " << score << " / 100.                      =\n";
        }
        else
        {
            cout << "= You won!                                     =\n";
            cout << "= You killed " << killedDuckCount << " ducks today! (" << escapedDuckCount << " ducks escaped) =\n";
            cout << "= Congrats!                                    =\n";
        }
        cout << "= If you want to play again, reload the game.  =\n";
        cout << "= Thanks for playing!                          =\n";
        cout << "================================================\n";
        displayOnlyOnce = false;
    }

    if (!gameOver)
    {
        /* Increment time */
        timeElapsed += deltaTimeSeconds;

        if (!debugMode)
        {
            /* Duck escape if running out of time or out of bullets */
            if (((timeElapsed >= 1250.0f / speed) && !isHit) || (bulletCount == 0 && !isHit))
                birdEscaped = true;
        }
        else
            timeElapsed = 0;

        /* Add delay for the first duck so as not to start flying before init on slow machines */
        if (isFirstBird)
        {
            if (timeElapsed >= 3)
            {
                timeElapsed = 0;
                isFirstBird = false;
            }
        }
        else
        {
            /* The "escape" state */
            if (birdEscaped)
            {
                /* If the "escape" state ended */
                if (reachedHeaven)
                {
                    /* Get a new angle */
                    randomAngle = transf2D::getRandomAngle();

                    timeElapsed = 0;

                    duckCount++;
                    escapedDuckCount++;
                    if (duckCount == 5)
                    {
                        /* Increase speed every 5 ducks */
                        speed = initialSpeed * (5.0f + speedCoefficient) / 5.0f;
                        speedCoefficient++;
                        duckCount = 0;
                    }

                    /* Compute new random starting position for the duck inside the grass */
                    coordinatesX = cx + (resolution.x - rectangleWidth) * transf2D::getStartingCoordinate();
                    coordinatesY = cy;

                    birdEscaped = false;
                    reachedHeaven = false;

                    /* If in debug mode, do not modify gameplay indicators */
                    if (!debugMode)
                    {
                        lifeCount--;
                        bulletCount = 3;
                        /* Decrease score by 15 if the duck escaped */
                        if (score > 15)
                            score -= 15;
                        else
                            score = 0;
                    }
                }
                /* If it's escaping */
                else
                {
                    randomAngle = 90;

                    /* Condition for the escape to end */
                    if (translateY > resolution.y * 9.0f / 8.0f)
                        reachedHeaven = true;
                }
            }
            /* The "dying" state, same as escaping */
            else if (isHit)
            {
                if (reachedFloor)
                {
                    randomAngle = transf2D::getRandomAngle();

                    timeElapsed = 0;

                    duckCount++;
                    killedDuckCount++;
                    if (duckCount == 5)
                    {
                        speed = initialSpeed * (5.0f + speedCoefficient) / 5.0f;
                        speedCoefficient++;
                        duckCount = 0;
                    }

                    coordinatesX = cx + (resolution.x - rectangleWidth) * transf2D::getStartingCoordinate();
                    coordinatesY = cy;

                    isHit = false;
                    reachedFloor = false;

                    if (!debugMode)
                    {
                        bulletCount = 3;
                        score += 5;
                    }
                }
                else
                {
                    /* But the angle is downward, not upward */
                    randomAngle = 270;

                    if (translateY < -rectangleHeight)
                        reachedFloor = true;
                }
            }
            /* If it's not dying or escaping, but it headbangs the margins */
            else if (headX >= resolution.x)
            {
                /* Compute the new bounce angle */
                if (randomAngle >= 0 && randomAngle <= 90)
                    randomAngle = 90 + (90 - randomAngle);
                else
                    randomAngle = 180 + (360 - randomAngle);
            }
            else if (headY >= resolution.y)
            {
                if (randomAngle >= 90 && randomAngle <= 180)
                    randomAngle = 180 + (180 - randomAngle);
                else
                    randomAngle = 270 + (90 - randomAngle);
            }
            else if (headX <= 0)
            {
                if (randomAngle >= 180 && randomAngle <= 270)
                    randomAngle = 270 + (270 - randomAngle);
                else
                    randomAngle = 180 - randomAngle;
            }
            else if (headY <= 0)
            {
                if (randomAngle >= 270 && randomAngle <= 360)
                    randomAngle = 360 - randomAngle;
                else
                    randomAngle = 90 + (270 - randomAngle);
            }

            /* Compute the bounce angle in radians */
            randomRadianAngle = transf2D::getRadiansFromAngle(randomAngle);

            /* Every time the duck moves, move its center coordinates */
            coordinatesX += deltaTimeSeconds * speed * cosf(randomRadianAngle);
            coordinatesY += deltaTimeSeconds * speed * sinf(randomRadianAngle);

            /* Compute the headCoordinates. rectangleWidth, headPositonWidth etc. are generalized
            so that if they ever change in Init(), it would still work */
            headX = coordinatesX +
                    (rectangleWidth - headPositionWidth) * cosf(randomRadianAngle) +
                    (headPositionHeight - rectangleHeight / 2.0f) * sinf(randomRadianAngle);
            headY = coordinatesY +
                    (rectangleWidth - headPositionWidth) * sinf(randomRadianAngle) +
                    (headPositionHeight - rectangleHeight / 2.0f) * cosf(randomRadianAngle);

            /* Compute where to move the duck */
            translateX = coordinatesX - rectangleWidth / 2.0f;
            translateY = coordinatesY - rectangleHeight / 2.0f;

            modelMatrix = glm::mat3(1);
            modelMatrix *= transf2D::Translate(translateX, translateY);

            modelMatrix *= transf2D::Translate(cx, cy);
            modelMatrix *= transf2D::Rotate(randomRadianAngle);
            modelMatrix *= transf2D::Translate(-cx, -cy);
        }

        if (debugMode)
        {
            RenderMesh2D(meshes["hitbox"], shaders["VertexColor"], modelMatrix);

            RenderMesh2D(meshes["bodyCenter"], shaders["VertexColor"], modelMatrix);

            RenderMesh2D(meshes["headCenter"], shaders["VertexColor"], modelMatrix);
        }

        RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

        RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

        RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

        /* Save the modelMatrix for the other wing */
        tmpModelMatrix = modelMatrix;

        if (leftAngularStep < transf2D::getRadiansFromAngle(30))
            leftAngularStep += deltaTimeSeconds;
        else
            leftAngularStep = transf2D::getRadiansFromAngle(-10);

        modelMatrix *= transf2D::Translate(cx, cy);
        modelMatrix *= transf2D::Rotate(leftAngularStep);
        modelMatrix *= transf2D::Translate(-cx, -cy);

        RenderMesh2D(meshes["leftArm"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tmpModelMatrix;

        if (rightAngularStep > transf2D::getRadiansFromAngle(-30))
            rightAngularStep -= deltaTimeSeconds;
        else
            rightAngularStep = transf2D::getRadiansFromAngle(10);

        modelMatrix *= transf2D::Translate(cx, cy);
        modelMatrix *= transf2D::Rotate(rightAngularStep);
        modelMatrix *= transf2D::Translate(-cx, -cy);

        RenderMesh2D(meshes["rightArm"], shaders["VertexColor"], modelMatrix);

        /* After arm rotation, restore modelMatrix */
        modelMatrix = tmpModelMatrix;
    }
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    /* Press T to enter debug mode */
    if (key == GLFW_KEY_T)
    {
        switch (debugMode)
        {
        case true:
            debugMode = false;
            break;
        default:
            debugMode = true;
            break;
        }
    }
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    glm::ivec2 resolution = window->GetResolution();

    /* Make the mouse coordinates alike the general ones, move (0, 0) to center of duck */
    glm::vec2 trueMouseCoordinates = { (float)mouseX, resolution.y - (float)mouseY };
    trueMouseCoordinates -= glm::vec2(coordinatesX, coordinatesY);

    glm::mat2 rotationMatrix = glm::transpose(
        glm::mat2(
            cosf(randomRadianAngle), sinf(randomRadianAngle),
            -sinf(randomRadianAngle), cosf(randomRadianAngle)
            )
        );

    /* Rotation the axes with the same angle as the duck*/
    trueMouseCoordinates = rotationMatrix * trueMouseCoordinates;

    /* If mouse coordinates are in rectangle of duck at press */
    if (trueMouseCoordinates.x >= -140.0f &&
        trueMouseCoordinates.x <= 140.0f &&
        trueMouseCoordinates.y >= -115.0f &&
        trueMouseCoordinates.y <= 115.0f &&
        !birdEscaped &&
        !isHit)
    {
        isHit = true;

        bulletCount--;
    }
    else if (!isFirstBird)
        bulletCount--;
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
