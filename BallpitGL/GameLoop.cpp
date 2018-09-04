#include "GameLoop.hpp"

// Prevent circular Dependencies
#include "UppWindow.hpp"
#include "World.hpp"
#include "Timer.hpp"
#include "Input.hpp"
#include "MasterRenderer.hpp"

namespace upp
{
    GameLoop::GameLoop()
    {
        window = nullptr;
        input = nullptr;
        timer = nullptr;
        running = false;
        minimized = false;
    }

    void GameLoop::initialize(UppWindow* window)
    {
        this->window = window;
        this->input = window->getInput();
        this->timer = window->getTimer();

        world = new World();
        world->initialize(window);

        window->setShowCursor(false);
    }

    void GameLoop::shutdown()
    {
        SHUTDOWN_AND_DELETE_OBJ(world);
    }

    void GameLoop::start()
    {
        const uint PHYSICS_FPS = 60;
        const float frametime = 1.0f / PHYSICS_FPS;
        const float maxCalcTime = frametime * 4;

        double lastFrame = timer->getTime();
        float accumulator = 0.0f;
        float worldTime = 0.0f;

        running = true;
        while (running)
        {
            // Calculate passed Time(delta)
            double thisFrame = timer->getTime();
            float delta = static_cast<float>(thisFrame - lastFrame);
            lastFrame = thisFrame;

            // Update Window
            window->handleMessages(minimized);
            // If X is pressed or alt-f4'ed
            if (window->shouldClose()) {
                window->stopGame();
            }
            checkInput();
            //printPerformanceStats(delta);

            accumulator += delta;
            if (accumulator > maxCalcTime) {
                accumulator = maxCalcTime; // Prevents spiral of death
            }

            while (accumulator > frametime) {
                world->update(frametime);
                worldTime += frametime;
                accumulator -= frametime;
            }

            float alpha = accumulator / frametime;
            if (!minimized) {
                world->render(alpha);
            }
        }
    }

    void GameLoop::stop()
    {
        running = false;
    }

    bool GameLoop::isRunning()
    {
        return running;
    }

    void GameLoop::framebuffer_resized(int width, int height)
    {
        if (width != 0 && height != 0) {
            glViewport(0, 0, width, height);
        }
    }

    void GameLoop::gameMinimizedChanged(bool minimized)
    {
        this->minimized = minimized;
    }

    void GameLoop::checkInput()
    {
        if (input->isKeyPressed(UPP_KEY_F11))
        {
            std::cout << "F11 Pressed" << std::endl;
            window->toggleFullscreen();
        }

        if (input->isKeyPressed(GLFW_KEY_V))
        {
            window->toggleVsync();
            std::cout << "Vsync set to: " << window->getVsync() << std::endl;
        }

        if (input->isKeyPressed(UPP_KEY_P))
        {
            std::cout << "P Pressed" << std::endl;
            window->toggleShowCursor();
        }

        if (input->isKeyDown(UPP_KEY_F)) {
            world->addRandomBall();
        }

        if (input->isKeyPressed(GLFW_KEY_R)) {
        }

        if (input->isKeyPressed(UPP_KEY_UP))
        {
            world->getRenderer()->toggleThroughPolygonModes();
        }

        if (input->isKeyDown(UPP_KEY_ESCAPE))
        {
            std::cout << "Escape pressed" << std::endl;
            window->stopGame();
        }
    }

    void GameLoop::toggleWireframe()
    {
        static bool wireframe = false;
        wireframe = !wireframe;
        if (wireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
    void GameLoop::printPerformanceStats(float delta)
    {
        static float minDelta = INFINITY;
        static float maxDelta = 0.0f;

        if (delta < minDelta) {
            minDelta = delta;
        }
        if (delta > maxDelta) {
            maxDelta = delta;
        }

        static uint frameCounter = 0;
        frameCounter++;
        if (frameCounter % 180 == 0) {
            std::cout << "Frame: " << frameCounter << std::endl;
            std::cout << "FPS: " << 1.0f / delta << std::endl;
            std::cout << "Max FPS: " << 1.0f / minDelta << std::endl;
            std::cout << "Min FPS: " << 1.0f / maxDelta << std::endl;
            maxDelta = 0.0f;
            minDelta = INFINITY;
        }
    }
}
