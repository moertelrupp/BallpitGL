#pragma once

// Includes
#include "UppIncludes.hpp"

namespace upp
{
    struct Vertex {
        glm::vec3 pos;
        glm::vec3 norm;

        Vertex(const glm::vec3& pos, const glm::vec3& norm)
        {
            this->pos = pos;
            this->norm = norm;
        }
    };
}
