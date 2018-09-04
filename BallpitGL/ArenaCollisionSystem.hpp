#pragma once

// Forward Declarations
namespace upp
{
    class BaseECSComponent;
}

// Includes
#include "UppIncludes.hpp"
#include "BaseECSSystem.hpp"

namespace upp
{
    class ArenaCollisionSystem : public BaseECSSystem
    {
    public:
        ArenaCollisionSystem() {}

        void initialize(float arenaWidth, float arenaHeight);
        void shutdown();

        virtual void updateComponents(float delta, BaseECSComponent** components);

    private:
        float halfArenaWidth;
        float halfArenaHeight;
    };
}