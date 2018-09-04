#pragma once

// Forward Declarations
namespace upp
{
    class MasterRenderer;
    class BaseECSComponent;
}

// Includes
#include "UppIncludes.hpp"
#include "BaseECSSystem.hpp"
#include "Mesh.hpp"

namespace upp
{
    class BallRenderSystem : public BaseECSSystem
    {
    public:
        BallRenderSystem() {}
        void initialize(MasterRenderer* renderer);
        void shutdown();

        virtual void preUpdate(float delta) override;
        virtual void updateComponents(float delta, BaseECSComponent** components) override;

    private:
        Mesh* ballMesh = nullptr;
        MasterRenderer* renderer = nullptr;
    };
}