#pragma once

// Forward Declarations
namespace upp
{
    class Input;
    class Timer;
    class GameLoop;
}

// Includes
#include "UppIncludes.hpp"

namespace upp
{
    class UppWindow
    {
    public:
        static UppWindow* getInstance();

        void initialize(bool fullscreen, bool vsync, int width, int height); // Allocates resources
        void shutdown(); // Frees resources
        void startGame(); // Starts Game Loop
        void stopGame(); // Stops Game Loop and closes Window

        bool shouldClose(); // If OS signaled the window to close (X pressed or alt-f4'ed)
        void swapBuffers(); // Swaps Framebuffers, used for presenting a rendered Image
        void handleMessages(bool blocking = false); // Handles OS-Messages like Inputs, Window Resize...

        // Window options
        void setVsync(bool vsync);
        bool getVsync();
        void toggleVsync();

        void setFullscreen(bool fullscreen);
        bool getFullscreen();
        void toggleFullscreen();

        void setShowCursor(bool showCursor);
        bool getShowCursor();
        void toggleShowCursor();

        // Getters
        Input* getInput();
        Timer* getTimer();
        GLFWwindow* getGLFWwindow();

        float getAspectRatio();
        int getWindowWidth();
        int getWindowHeight();
        int getFramebufferWidth();
        int getFramebufferHeight();

    private:
        UppWindow();

        void initializeGLFW();
        void createGlfwWindow(bool fullscreen, int width, int height);
        void initializeGlad();
        void shutdownGLFW();

        void framebuffer_size_changed(int width, int height);
        void window_size_changed(int width, int height);
        void mouse_changed(double xPos, double yPos);
        void key_changed(int key, int scancode, int action, int mods);
        void window_pos_changed(int xPos, int yPos);
        void iconify_changed(int iconified);

        // Callbacks
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void window_size_callback(GLFWwindow* window, int width, int height);
        static void mouse_callback(GLFWwindow* window, double xPos, double yPos);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void window_pos_callback(GLFWwindow* window, int xPos, int yPos);
        static void iconify_callback(GLFWwindow* window, int iconified);
        static void error_callback(int errorCode, const char* error);

    private:
        static UppWindow* instance; // Singleton Pattern
        bool initialized;

        GLFWwindow* window;
        GameLoop* gameLoop;
        Input* input;
        Timer* timer;

        // Window Attributes
        bool fullscreen;
        bool minimized;
        bool vsync;
        bool showCursor;
        // Window Size
        int framebufferWidth, framebufferHeight;
        int windowWidth, windowHeight;
        int prev_windowWidth, prev_windowHeight;
        // Window Position
        int windowPosX, windowPosY;
        int prev_WindowPosX, prev_WindowPosY;
    };
}

