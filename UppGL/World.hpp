#pragma once

// Forward Declarations
namespace upp
{
    class UppWindow;
    class MasterRenderer;
    class Input;
    class Camera;
    class Mesh;
    class ECS;
    class BallRenderSystem;
    class MotionSystem;
    class ArenaCollisionSystem;
}

// Includes
#include "UppIncludes.hpp"

namespace upp
{
    class World 
    {
    public:
        World() {};

        void initialize(UppWindow* window);
        void shutdown();

        void update(float delta);
        void render(float alpha);

        void addRandomBall();

        MasterRenderer* getRenderer() { return renderer; };

    private:
        // Window Control
        UppWindow* window = nullptr;
        Input* input = nullptr;

        // Rendering
        MasterRenderer* renderer = nullptr;
        Camera* camera = nullptr;

        const float arenaWidth = 20.0f;
        Mesh* arenaMesh = nullptr;

        // ECS:
        ECS* ecs = nullptr;
        BallRenderSystem* ballRenderSys = nullptr;
        MotionSystem* motionSys = nullptr;
        ArenaCollisionSystem* arenaCollisionSys = nullptr;
        uint ballCount = 0;

        NULL_COPY_AND_ASSIGN(World);
    };
}