#include "Texture.hpp"

namespace upp
{
    Texture::Texture(std::string filename, GLint format)
    {
        textureID = 0;
        width = 0;
        height = 0;

        initialize(filename, format);
    }

    void Texture::initialize(std::string filename, GLint format)
    {
        unsigned char* data = loadFile("Resources\\Textures\\" + filename);
        createTexture(data, format);
        delete[] data;
    }

    void Texture::shutdown()
    {
        if (textureID != 0)
        {
            glDeleteTextures(1, &textureID);
            textureID = 0;
        }
    }

    void Texture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    void Texture::createTexture(unsigned char* data, GLint format)
    {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        // Mipmap
        glGenerateMipmap(GL_TEXTURE_2D);

        // Wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Unbind
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    unsigned char* Texture::loadFile(std::string filename)
    {
        unsigned char* data;
        int nChannels;
        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(filename.c_str(), &width, &height, &nChannels, 0);

        if (!data)
        {
            THROW_EXCEPTION("Couldn't load texture: " + filename);
        }

        return data;
    }

}
