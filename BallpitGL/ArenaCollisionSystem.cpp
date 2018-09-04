#include "ArenaCollisionSystem.hpp"

// Prevent circular Dependencies
#include "BallComponents.hpp"

namespace upp
{
    void ArenaCollisionSystem::initialize(float arenaWidth, float arenaHeight)
    {
        addComponentType(PositionComponent::ID);
        addComponentType(MotionComponent::ID);
        addComponentType(RadiusComponent::ID);

        this->halfArenaHeight = arenaWidth / 2.0f;
        this->halfArenaHeight = arenaHeight / 2.0f;
    }

    void ArenaCollisionSystem::shutdown()
    {
    }

    void ArenaCollisionSystem::updateComponents(float delta, BaseECSComponent** components)
    {
        glm::vec2& position = ((PositionComponent*)components[0])->position;
        glm::vec2& velocity = ((MotionComponent*)components[1])->velocity;
        float& radius = ((RadiusComponent*)components[2])->radius;

        // Left and right bounds
        if (position.x + radius > halfArenaWidth) {
            position.x = halfArenaWidth - radius;
            velocity.x *= -1;
        }
        else if (position.x - radius < halfArenaWidth) {
            position.x = -halfArenaWidth + radius;
            velocity.x *= -1;
        }

        // Upper and lower bounds
        if (position.y + radius > halfArenaHeight) {
            position.y = halfArenaHeight - radius;
            velocity.y *= -1;
        }
        else if (position.y - radius < halfArenaHeight) {
            position.y = -halfArenaHeight + radius;
            velocity.y *= -1;
        }
    }
}

