#pragma once

// Includes
#include "UppIncludes.hpp"

// Defines for Keys:
#define UPP_KEY_UP GLFW_KEY_UP
#define UPP_KEY_DOWN GLFW_KEY_DOWN
#define UPP_KEY_LEFT GLFW_KEY_LEFT
#define UPP_KEY_RIGHT GLFW_KEY_RIGHT
#define UPP_KEY_W GLFW_KEY_W
#define UPP_KEY_A GLFW_KEY_A
#define UPP_KEY_S GLFW_KEY_S
#define UPP_KEY_D GLFW_KEY_D
#define UPP_KEY_ESCAPE GLFW_KEY_ESCAPE
#define UPP_KEY_F11 GLFW_KEY_F11
#define UPP_KEY_P GLFW_KEY_P
#define UPP_KEY_SHIFT GLFW_KEY_LEFT_SHIFT
#define UPP_KEY_F GLFW_KEY_F

namespace upp
{
    class Input
    {
    public:
        Input();

        void processMouseInput(double xPos, double yPos);
        void processKeyInput(int key, int scancode, int action, int mods);
        void updateInput(); // Resets all KeyPressed events 
        void resetInput();

        bool isKeyDown(int keyCode);
        bool isKeyPressed(int keyCode);

        float mousePosX, mousePosY;

    private:
        void setKeyDown(int keycode, bool down);
        void setKeyPressed(int keycode, bool pressed);
        void resetKeyPressed(); // Doesn't cost a lot of performance

    private:
        static constexpr int KEY_COUNT = 512;
        bool keyDown[KEY_COUNT]; // Is true while a key is down
        bool keyPressed[KEY_COUNT]; // Is true when a key when the key was just pressed (Only true for 1 Frame)
        int resetNextFrame[KEY_COUNT]; // Helper
        int resetCount = 0;
    };
}