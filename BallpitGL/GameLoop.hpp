#pragma once

// Includes
#include "UppIncludes.hpp"

// Forward declarations
namespace upp
{
    class UppWindow;
    class Input;
    class Timer;
    class World;
}

namespace upp
{
    class GameLoop
    {
    public:
        GameLoop();

        void initialize(UppWindow* window);
        void shutdown();

        void start();
        void stop();
        bool isRunning();

        void framebuffer_resized(int width, int height);
        void gameMinimizedChanged(bool minimized);

    private:
        void checkInput();
        void toggleWireframe();
        void printPerformanceStats(float delta);

    private:
        UppWindow* window;
        Input* input;
        Timer* timer;
        World* world;

        bool running, minimized;
    };
}