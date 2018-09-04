#include "MotionSystem.hpp"

// Prevent circular Dependencies
#include "BallComponents.hpp"

namespace upp
{
    MotionSystem::MotionSystem()
    {
    }

    void MotionSystem::initialize()
    {
        addComponentType(PositionComponent::ID);
        addComponentType(MotionComponent::ID);
    }

    void MotionSystem::shutdown()
    {
    }

    void MotionSystem::updateComponents(float delta, BaseECSComponent** components)
    {
        glm::vec2& position = ((PositionComponent*)components[0])->position;
        glm::vec2& velocity = ((MotionComponent*)components[1])->velocity;

        position += velocity * delta;
    }
}


