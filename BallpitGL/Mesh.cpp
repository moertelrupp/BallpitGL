#include "Mesh.hpp"

namespace upp
{
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    {
        this->vertices = vertices;
        this->indices = indices;

        setupMesh();
    }

    void Mesh::use()
    {
        glBindVertexArray(VAO);
    }

    void Mesh::draw()
    {
        unsigned int offset = 0;
        glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, (void*)offset);
    }

    void Mesh::setupMesh()
    {
        // Generate Buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind VAO
        glBindVertexArray(VAO);

        // Bind Vertex Data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        // Set Vertex Attributes
        unsigned int offset = 0;
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);
        glEnableVertexAttribArray(0);

        offset = sizeof(glm::vec3);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);
        glEnableVertexAttribArray(1);

        // Set Element buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

        drawCount = indices.size();

        // Unbind
        glBindVertexArray(0);
    }

}
