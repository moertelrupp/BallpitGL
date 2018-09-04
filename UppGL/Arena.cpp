#include "Arena.hpp"

namespace upp
{
    Mesh* Arena::createArenaMesh(float width, float height, float thickness)
    {
        return createGeometry(width, height, thickness);
    }

    Mesh* Arena::createGeometry(float width, float height, float thickness)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        glm::vec3 positions[] = {
            glm::vec3(-width / 2.0f, width / 2.0f, height / 2.0f),
            glm::vec3(+width / 2.0f, width / 2.0f, height / 2.0f),
            glm::vec3(+width / 2.0f, -width / 2.0f, height / 2.0f),
            glm::vec3(-width / 2.0f, -width / 2.0f, height / 2.0f),

            glm::vec3(-width / 2.0f, width / 2.0f, -height / 2.0f),
            glm::vec3(+width / 2.0f, width / 2.0f, -height / 2.0f),
            glm::vec3(+width / 2.0f, -width / 2.0f, -height / 2.0f),
            glm::vec3(-width / 2.0f, -width / 2.0f, -height / 2.0f),

            glm::vec3(-width / 2.0f - thickness, width / 2.0f + thickness, height / 2.0f),
            glm::vec3(+width / 2.0f + thickness, width / 2.0f + thickness, height / 2.0f),
            glm::vec3(+width / 2.0f + thickness, -width / 2.0f - thickness, height / 2.0f),
            glm::vec3(-width / 2.0f - thickness, -width / 2.0f - thickness, height / 2.0f),

            glm::vec3(-width / 2.0f - thickness, width / 2.0f + thickness, -height / 2.0f),
            glm::vec3(+width / 2.0f + thickness, width / 2.0f + thickness, -height / 2.0f),
            glm::vec3(+width / 2.0f + thickness, -width / 2.0f - thickness, -height / 2.0f),
            glm::vec3(-width / 2.0f - thickness, -width / 2.0f - thickness, -height / 2.0f),

            glm::vec3(-width / 2.0f, width / 2.0f + thickness, height / 2.0f),
            glm::vec3(+width / 2.0f, width / 2.0f + thickness, height / 2.0f),
            glm::vec3(+width / 2.0f, -width / 2.0f - thickness, height / 2.0f),
            glm::vec3(-width / 2.0f, -width / 2.0f - thickness, height / 2.0f),

            glm::vec3(-width / 2.0f, width / 2.0f + thickness, -height / 2.0f),
            glm::vec3(+width / 2.0f, width / 2.0f + thickness, -height / 2.0f),
            glm::vec3(+width / 2.0f, -width / 2.0f - thickness, -height / 2.0f),
            glm::vec3(-width / 2.0f, -width / 2.0f - thickness, -height / 2.0f),
        };

        glm::vec3 left(-1.0f, 0.0f, 0.0f);
        glm::vec3 right(1.0f, 0.0f, 0.0f);
        glm::vec3 up(0.0f, 1.0f, 0.0f);
        glm::vec3 down(0.0f, -1.0f, 0.0f);
        glm::vec3 front(0.0f, 0.0f, 1.0f);
        glm::vec3 back(0.0f, 0.0f, -1.0f);

        addFace(vertices, indices, positions, 0, 3, 7, 4, right); // Left Inner Face
        addFace(vertices, indices, positions, 1, 5, 6, 2, left); // Right Inner Face
        addFace(vertices, indices, positions, 0, 4, 5, 1, down); // Upper Inner Face
        addFace(vertices, indices, positions, 2, 6, 7, 3, up); // Lower Inner Face

        addFace(vertices, indices, positions, 8, 12, 15, 11, left); // Left Outer Face
        addFace(vertices, indices, positions, 9, 10, 14, 13, right); // Right Outer Face
        addFace(vertices, indices, positions, 8, 9, 13, 12, up); // Upper Outer Face
        addFace(vertices, indices, positions, 10, 11, 15, 14, up); // Lower Outer Face

        addFace(vertices, indices, positions, 8, 11, 19, 16, front); // Left Front Face
        addFace(vertices, indices, positions, 9, 17, 18, 10, front); // Right Front Face
        addFace(vertices, indices, positions, 17, 16, 0, 1, front); // Upper Front Face
        addFace(vertices, indices, positions, 3, 19, 18, 2, front); // Lower Front Face

        addFace(vertices, indices, positions, 20, 23, 15, 12, back); // Left Back Face
        addFace(vertices, indices, positions, 13, 14, 22, 21, back); // Right Back Face
        addFace(vertices, indices, positions, 20, 21, 5, 4, back); // Upper Back Face
        addFace(vertices, indices, positions, 7, 6, 22, 23, back); // Lower Back Face

        return new Mesh(vertices, indices);
    }


    void Arena::addFace(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, glm::vec3* positions,
        int p0, int p1, int p2, int p3, const glm::vec3& normal)
    {
        unsigned int size = vertices.size();

        vertices.push_back(Vertex(positions[p0], normal));
        vertices.push_back(Vertex(positions[p1], normal));
        vertices.push_back(Vertex(positions[p2], normal));
        vertices.push_back(Vertex(positions[p3], normal));

        indices.push_back(size);
        indices.push_back(size + 1);
        indices.push_back(size + 2);
        indices.push_back(size);
        indices.push_back(size + 2);
        indices.push_back(size + 3);
    }
}

