#pragma once

// Includes
#include "UppIncludes.hpp"

namespace upp
{
    struct Material
    {
        Material(glm::vec3& color)
            : color(color) {}

        glm::vec3 color;
    };

    struct DirLight
    {
        DirLight(glm::vec3& color, glm::vec3& dir)
            : color(color), dir(dir) {}

        glm::vec3 color;
        glm::vec3 dir;
    };

    struct AmbientLight
    {
        AmbientLight(glm::vec3& color)
            : color(color) {}

        glm::vec3 color;
    };
}