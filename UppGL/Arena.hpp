#pragma once

// Includes
#include "UppIncludes.hpp"
#include "Mesh.hpp"
#include "Vertex.hpp"

namespace upp
{
    class Arena
    {
    public:
        static Mesh* createArenaMesh(float width, float height, float thickness);

    private:
        static Mesh* createGeometry(float width, float height, float thickness);
        static void addFace(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, glm::vec3* positions, int p0, int p1, int p2, int p3, const glm::vec3& normal);
    };
}
