#pragma once

// Includes
#include "UppIncludes.hpp"

// Forward Declarations
namespace upp
{
    class UppWindow;
    class Input;
}

namespace upp
{
    class Camera
    {
    public:
        Camera(UppWindow* window, Input* input, glm::vec3 pos);

        glm::vec3 getPos();
        glm::vec3 getDir();
        void update(float deltatime);
        void resetMouseMovement();
        glm::mat4 calcView();
        glm::mat4 calcProjection();

    private:
        UppWindow* window;
        Input* input;

        glm::vec3 pos;
        glm::vec3 dir;
        glm::vec3 up;

        float fov, speed, sensitivity;
        float yaw, pitch;
        float lastX, lastY;
        bool firstMouse;
    };
}
