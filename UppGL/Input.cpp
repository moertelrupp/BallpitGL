#include "Input.hpp"

namespace upp
{
    Input::Input()
    {
        resetInput();
    }

    void Input::processMouseInput(double xPos, double yPos)
    {
        mousePosX = xPos;
        mousePosY = yPos;
    }

    void Input::processKeyInput(int key, int scancode, int action, int mods)
    {
        switch (action)
        {
        case GLFW_REPEAT:
            setKeyDown(key, true);
            break;
        case GLFW_RELEASE:
            setKeyDown(key, false);
            break;
        case GLFW_PRESS:
            setKeyPressed(key, true);
            setKeyDown(key, true);
            break;
        }
    }

    void Input::updateInput()
    {
        resetKeyPressed();
    }

    void Input::resetInput()
    {
        for (int i = 0; i < KEY_COUNT; i++)
        {
            keyDown[i] = false;
            keyPressed[i] = false;
            resetNextFrame[i] = 0;
        }
        resetCount = 0;
        mousePosX = mousePosY = 0.0f;
    }

    bool Input::isKeyDown(int keyCode)
    {
        if (keyCode >= KEY_COUNT)
        {
            return false;
        }
        return keyDown[keyCode];
    }

    bool Input::isKeyPressed(int keyCode)
    {
        if (keyCode >= KEY_COUNT)
        {
            return false;
        }
        return keyPressed[keyCode];
    }

    void Input::setKeyDown(int keyCode, bool down)
    {
        if (keyCode < KEY_COUNT)
        {
            keyDown[keyCode] = down;
        }
    }

    void Input::setKeyPressed(int keyCode, bool pressed)
    {
        if (keyCode < KEY_COUNT && resetCount < KEY_COUNT)
        {
            keyPressed[keyCode] = pressed;
            resetNextFrame[resetCount] = keyCode;
            resetCount++;
        }
    }

    void Input::resetKeyPressed()
    {
        for (int i = 0; i < resetCount; i++)
        {
            keyPressed[resetNextFrame[i]] = false;
        }
        resetCount = 0;
    }

}