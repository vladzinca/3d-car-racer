#pragma once

#include "utils/glm_utils.h"


namespace transf2D
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        return glm::mat3(
            1, 0, 0,
            0, 1, 0,
            translateX, translateY, 1);

    }

    // Scale matrix
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
        return glm::mat3(
            scaleX, 0, 0,
            0, scaleY, 0,
            0, 0, 1);

    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        return glm::mat3(
            cosf(radians), sinf(radians), 0,
            -sinf(radians), cosf(radians), 0,
            0, 0, 1);

    }

    // Get the desired random angle
    inline int getRandomAngle()
    {
        if ((rand() % 2) == 0)
            return rand() % 50 + 15;
        else
            return rand() % 50 + 105;
    }

    // Get radians from degrees
    inline float getRadiansFromAngle(int angle)
    {
        return (float)angle * (float)M_PI / 180.0f;
    }

    // Get starting coordinate
    inline float getStartingCoordinate()
    {
        return (float)(rand() % 50 + 25) / 100.0f;
    }
}   // namespace transf2D
