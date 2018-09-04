#pragma once

// Includes
#include "UppIncludes.hpp"
#include "Mesh.hpp"
#include "Vertex.hpp"

namespace upp
{
    class BallModel
    {
    public:
        static Mesh* createBallMesh(float radius, int level);

    private:
        static Mesh* createGeometry(float radius, int level);
        static void refineIsoSphere(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, float radius);
        static void refineTriangle(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, uint i0, uint i1, uint i2, float radius);
    };
}
