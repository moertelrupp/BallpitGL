#pragma once

// Includes
#include "UppIncludes.hpp"
#include "Vertex.hpp"

namespace upp
{
    class Mesh
    {
    public:
        /* Mesh Data */
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        /* Functions */
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        void use();
        void draw();

    private:
        void setupMesh();

    private:
        unsigned int VAO, VBO, EBO;
        unsigned int drawCount;
    };
}


