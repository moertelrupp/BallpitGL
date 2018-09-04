#pragma once

// Includes
#include "UppIncludes.hpp"
#include "BaseECSSystem.hpp"

namespace upp
{
    class MotionSystem : public BaseECSSystem
    {
    public:
        MotionSystem();
        void initialize();
        void shutdown();

        virtual void updateComponents(float delta, BaseECSComponent** components) override;
    };
}