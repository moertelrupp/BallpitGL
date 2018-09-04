#include "BallRenderSystem.hpp"

// Prevent circular Dependencies
#include "MasterRenderer.hpp"
#include "ECSComponent.hpp"
#include "BallComponents.hpp"
#include "BallModel.hpp"
#include "ArenaCollisionSystem.hpp"

namespace upp
{
    void BallRenderSystem::initialize(MasterRenderer* renderer)
    {
        addComponentType(PositionComponent::ID);
        addComponentType(RadiusComponent::ID);
        addComponentType(MaterialComponent::ID);

        this->renderer = renderer;
        ballMesh = BallModel::createBallMesh(1.0f, 4);
    }

    void BallRenderSystem::shutdown()
    {
        DELETE_OBJ(ballMesh);
    }

    void BallRenderSystem::preUpdate(float delta)
    {
        ballMesh->use();
    }

    void BallRenderSystem::updateComponents(float delta, BaseECSComponent** components)
    {
        glm::vec2& position = (*((PositionComponent*)components[0])).position;
        float& radius = (*((RadiusComponent*)components[1])).radius;
        Material& material = (*((MaterialComponent*)components[1])).material;

        static glm::mat4 modelMat = glm::mat4(1.0f);

        modelMat[0][0] = radius;
        modelMat[1][1] = radius;
        modelMat[2][2] = radius;
        modelMat[3][0] = position.x;
        modelMat[3][1] = position.y;

        renderer->setModelMat(modelMat);
        renderer->setMaterial(material);
        ballMesh->draw();
    }
}
