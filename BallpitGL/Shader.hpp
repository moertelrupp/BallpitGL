// Include Guards
#pragma once

// Includes
#include "UppIncludes.hpp"

namespace upp
{
    class Shader
    {
    public:
        Shader(std::string vertexShader, std::string fragmentShader);

        void use();
        unsigned int getProgramID();

        int getUniformLoc(std::string name, bool throwException = true);
        void setUniform3f(std::string name, float x, float y, float z);
        void setUniform1f(std::string name, float value);
        void setUniform1i(std::string name, int value);

        void setUniformMat4f(int location, const glm::mat4& matrix);
        void setUniformVec3f(int location, const glm::vec3& vector);

    private:
        std::string loadFile(std::string path);
        unsigned int programID;
    };
}
