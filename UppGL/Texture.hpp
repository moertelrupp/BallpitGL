#pragma once

// Includes
#include "UppIncludes.hpp"

namespace upp
{
    class Texture
    {
    public:
        Texture(std::string filename, GLint format);
        void shutdown();

        void bind();

    private:
        unsigned int textureID;
        int width, height;

        void initialize(std::string filename, GLint format);
        void createTexture(unsigned char* data, GLint format);
        unsigned char* loadFile(std::string filename);
    };
}
