#include "Camera.hpp"

// Prevent circular Dependencies
#include "UppWindow.hpp"
#include "Input.hpp"

namespace upp
{
    Camera::Camera(UppWindow* window, Input* input, glm::vec3 pos)
    {
        this->window = window;
        this->input = input;
        this->pos = pos;
        up = glm::vec3(0.0f, 1.0f, 0.0f);

        pitch = 0;
        yaw = 270;
        fov = 90.0f;
        speed = 10.0f;
        sensitivity = 0.05f;
        firstMouse = true;
    }

    glm::vec3 Camera::getPos()
    {
        return pos;
    }

    glm::vec3 Camera::getDir()
    {
        return dir;
    }

    void Camera::update(float deltatime)
    {
        float movement = speed * deltatime;

        if (input->isKeyDown(UPP_KEY_SHIFT))
        {
            movement *= 10;
        }

        if (input->isKeyDown(UPP_KEY_W))
        {
            pos = pos + dir * movement;
        }

        if (input->isKeyDown(UPP_KEY_S))
        {
            pos = pos - dir * movement;
        }

        if (input->isKeyDown(UPP_KEY_A))
        {
            pos = pos - glm::cross(dir, up) * movement;
        }

        if (input->isKeyDown(UPP_KEY_D))
        {
            pos = pos + glm::cross(dir, up) * movement;
        }



        if (firstMouse  && input->mousePosX != 0 && input->mousePosY != 0) // this bool variable is initially set to true
        {
            lastX = input->mousePosX;
            lastY = input->mousePosY;
            firstMouse = false;
        }
        else
        {
            float xOffset = input->mousePosX - lastX;
            float yOffset = lastY - input->mousePosY;
            lastX = input->mousePosX;
            lastY = input->mousePosY;

            xOffset *= sensitivity;
            yOffset *= sensitivity;

            yaw += xOffset;
            pitch += yOffset;

            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;

            dir.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
            dir.y = sin(glm::radians(pitch));
            dir.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        }
    }

    void Camera::resetMouseMovement()
    {
        firstMouse = true;
    }

    glm::mat4 Camera::calcView()
    {
        glm::mat4 view = glm::lookAt(pos, pos + dir, up);
        return view;
    }

    glm::mat4 Camera::calcProjection()
    {
        glm::mat4 projection = glm::perspective(glm::radians(fov / 2.0f), window->getAspectRatio(), 0.1f, 10000.0f);
        return projection;
    }
}
