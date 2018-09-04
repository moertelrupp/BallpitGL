#pragma once

// Includes
#include "UppIncludes.hpp"
#include "ECSComponent.hpp"
#include "LightingData.hpp"

namespace upp
{
    struct PositionComponent : public ECSComponent<PositionComponent>
    {
        PositionComponent(glm::vec2& pos) : position(pos) {}
        glm::vec2 position;
    };

    struct MotionComponent : public ECSComponent<MotionComponent>
    {
        MotionComponent(glm::vec2& velocity) : velocity(velocity) {}
        glm::vec2 velocity;
    };

    struct RadiusComponent : public ECSComponent<RadiusComponent>
    {
        RadiusComponent(float radius) : radius(radius) {}
        float radius;
    };

    struct MaterialComponent : public ECSComponent<MaterialComponent>
    {
        MaterialComponent(Material& mat) : material(mat) {}
        Material material;
    };
}