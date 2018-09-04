#include "Shader.hpp"

namespace upp
{
    Shader::Shader(std::string vertexShaderFile, std::string fragmentShaderFile)
    {
        std::string vertexCode = loadFile("Resources\\Shaders\\" + vertexShaderFile);
        std::string fragmentCode = loadFile("Resources\\Shaders\\" + fragmentShaderFile);
        const GLchar* vertexSource = vertexCode.c_str();
        const GLchar* fragmentSource = fragmentCode.c_str();

        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        // vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexSource, NULL);
        glCompileShader(vertex);
        // print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            THROW_EXCEPTION("Vertexshader compilation failed: " + std::string(infoLog) + "\r\n");
        };

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentSource, NULL);
        glCompileShader(fragment);
        // print compile errors if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            THROW_EXCEPTION("Fragmentshader compilation failed: " + std::string(infoLog) + "\r\n");
        };

        // shader Program
        programID = glCreateProgram();
        glAttachShader(programID, vertex);
        glAttachShader(programID, fragment);
        glLinkProgram(programID);
        // print linking errors if any
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(programID, 512, NULL, infoLog);
            std::cout << "Linking shader program failed: " << infoLog << std::endl;
        }

        // delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Shader::use()
    {
        glUseProgram(programID);
    }

    unsigned int Shader::getProgramID()
    {
        return programID;
    }

    int Shader::getUniformLoc(std::string name, bool throwException)
    {
        int loc = glGetUniformLocation(programID, name.c_str());
        if (throwException && loc == -1)
        {
            THROW_EXCEPTION("Couldn't get Uniform location: " + name + "!");
        }
        return loc;
    }

    void Shader::setUniform3f(std::string name, float x, float y, float z)
    {
        // Get Location
        unsigned int uniformLoc = glGetUniformLocation(programID, name.c_str());
        // Set uniform if available
        if (uniformLoc != -1)
        {
            use();
            glUniform3f(uniformLoc, x, y, z);
        }
        else
        {
            THROW_EXCEPTION("Couldn't find uniform: " + name);
        }
    }

    void Shader::setUniform1f(std::string name, float value)
    {
        // Get Location
        unsigned int uniformLoc = glGetUniformLocation(programID, name.c_str());
        // Set uniform if available
        if (uniformLoc != -1)
        {
            use();
            glUniform1f(uniformLoc, value);
        }
        else
        {
            THROW_EXCEPTION("Couldn't find uniform: " + name);
        }
    }

    void Shader::setUniform1i(std::string name, int value)
    {
        // Get Location
        unsigned int uniformLoc = glGetUniformLocation(programID, name.c_str());
        // Set uniform if available
        if (uniformLoc != -1)
        {
            use();
            glUniform1i(uniformLoc, value);
        }
        else
        {
            THROW_EXCEPTION("Couldn't find uniform: " + name);
        }
    }

    void Shader::setUniformMat4f(int location, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::setUniformVec3f(int location, const glm::vec3& vector)
    {
        glUniform3fv(location, 1, glm::value_ptr(vector));
    }

    std::string Shader::loadFile(std::string path)
    {
        std::ifstream file;
        std::string result = "";

        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            file.open(path);
            std::stringstream stream;
            // read file's buffer contents into streams
            stream << file.rdbuf();
            // close file handlers
            file.close();
            // convert stream into string
            result = stream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        return result;
    }

}
