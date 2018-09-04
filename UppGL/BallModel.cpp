#include "BallModel.hpp"

namespace upp
{
    Mesh* BallModel::createBallMesh(float radius, int level)
    {
        return createGeometry(radius, level);
    }

    Mesh* BallModel::createGeometry(float radius, int level)
    {
        float de = radius / sqrtf(3.0f);

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        glm::vec3 a(-de, +de, -de);
        glm::vec3 b(+de, +de, +de);
        glm::vec3 c(-de, -de, +de);
        glm::vec3 d(+de, -de, -de);

        vertices.push_back(Vertex(a, a));
        vertices.push_back(Vertex(b, b));
        vertices.push_back(Vertex(c, c));
        vertices.push_back(Vertex(d, d));

        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(1);

        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(3);

        indices.push_back(1);
        indices.push_back(2);
        indices.push_back(3);

        indices.push_back(0);
        indices.push_back(3);
        indices.push_back(2);

        for (int i = 0; i < level; i++)
        {
            refineIsoSphere(vertices, indices, radius);
        }

        for (int i = 0; i < vertices.size(); i++)
        {
            vertices[i].pos = glm::normalize(vertices[i].pos) * radius;
            //std::cout << "Length of vertex " << i << ": " << glm::length(vertices[i].pos) << std::endl;
        }

        return new Mesh(vertices, indices);
    }

    void BallModel::refineIsoSphere(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, float radius)
    {
        std::vector<unsigned int> newIndices;

        if (indices.size() % 3 != 0)
        {
            THROW_EXCEPTION("Indices aren't a multiple of 3!");
        }

        for (unsigned int i = 0; i < indices.size(); i += 3)
        {
            unsigned int i0 = indices[i];
            unsigned int i1 = indices[i + 1];
            unsigned int i2 = indices[i + 2];

            refineTriangle(vertices, newIndices, i0, i1, i2, radius);
        }

        indices = newIndices;
    }

    void BallModel::refineTriangle(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, uint i0, uint i1, uint i2, float radius)
    {
        glm::vec3 pos3 = glm::normalize((vertices[i0].pos + vertices[i1].pos)) * radius;
        glm::vec3 pos4 = glm::normalize((vertices[i1].pos + vertices[i2].pos)) * radius;
        glm::vec3 pos5 = glm::normalize((vertices[i2].pos + vertices[i0].pos)) * radius;


        //glm::vec3 pos3 = (vertices[i0].pos + vertices[i1].pos) / 2.0f;
        //glm::vec3 pos4 = (vertices[i1].pos + vertices[i2].pos) / 2.0f;
        //glm::vec3 pos5 = (vertices[i2].pos + vertices[i0].pos) / 2.0f;

        uint i3 = vertices.size();
        uint i4 = i3 + 1;
        uint i5 = i4 + 1;
        // Add new Vertices
        vertices.push_back(Vertex(pos3, pos3));
        vertices.push_back(Vertex(pos4, pos4));
        vertices.push_back(Vertex(pos5, pos5));
        // Add indices
        indices.push_back(i0);
        indices.push_back(i3);
        indices.push_back(i5);

        indices.push_back(i3);
        indices.push_back(i1);
        indices.push_back(i4);

        indices.push_back(i3);
        indices.push_back(i4);
        indices.push_back(i5);

        indices.push_back(i2);
        indices.push_back(i5);
        indices.push_back(i4);
    }
}
