#pragma once

#include "utils/glm_utils.h"

namespace transf3D
{
    inline glm::mat4 Translate(float translateX, float translateY, float translateZ)
    {
        return glm::transpose(
            glm::mat4(
                1, 0, 0, translateX,
                0, 1, 0, translateY,
                0, 0, 1, translateZ,
                0, 0, 0, 1)
        );
    }

    inline glm::mat4 Scale(float scaleX, float scaleY, float scaleZ)
    {
        return glm::transpose(
            glm::mat4(
                scaleX, 0, 0, 0,
                0, scaleY, 0, 0,
                0, 0, scaleZ, 0,
                0, 0, 0, 1)
        );
    }

    inline glm::mat4 RotateOZ(float radians)
    {
        return glm::transpose(
            glm::mat4(
                cosf(radians), -sinf(radians), 0, 0,
                sinf(radians), cosf(radians), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1)
        );
    }

    inline glm::mat4 RotateOY(float radians)
    {
        return glm::transpose(
            glm::mat4(
                cosf(radians), 0, sinf(radians), 0,
                0, 1, 0, 0,
                -sinf(radians), 0, cosf(radians), 0,
                0, 0, 0, 1)
        );
    }

    inline glm::mat4 RotateOX(float radians)
    {
        return glm::transpose(
            glm::mat4(
                1, 0, 0, 0,
                0, cosf(radians), -sinf(radians), 0,
                0, sinf(radians), cosf(radians), 0,
                0, 0, 0, 1)
        );
    }

}
