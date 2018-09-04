#include "World.hpp"

// Prevent circular Dependencies
#include "UppWindow.hpp"
#include "Input.hpp"
#include "MasterRenderer.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "ECS.hpp"
#include "BallRenderSystem.hpp"
#include "ArenaCollisionSystem.hpp"
#include "MotionSystem.hpp"
#include "Arena.hpp"
#include "LightingData.hpp"
#include "Random.hpp"
#include "BallComponents.hpp"
#include "Timer.hpp"

namespace upp
{
    void World::initialize(UppWindow* window)
    {
        this->window = window;
        this->input = window->getInput();

        ecs = new ECS();
        ballRenderSys = new BallRenderSystem();
        arenaCollisionSys = new ArenaCollisionSystem();
        motionSys = new MotionSystem();

        renderer = new MasterRenderer();
        camera = new Camera(window, input, glm::vec3(0.0f, 0.0f, 20.0f));
        arenaMesh = Arena::createArenaMesh(arenaWidth, 3.0f, 1.0f);

        // Renderer
        renderer->initialize();
        ballRenderSys->initialize(renderer);
        arenaCollisionSys->initialize(arenaWidth, arenaWidth);
        motionSys->initialize();
    }

    void World::shutdown()
    {
        SHUTDOWN_AND_DELETE_OBJ(renderer);
        SHUTDOWN_AND_DELETE_OBJ(ballRenderSys);
        SHUTDOWN_AND_DELETE_OBJ(arenaCollisionSys);
        SHUTDOWN_AND_DELETE_OBJ(motionSys);
        DELETE_OBJ(arenaMesh);
        DELETE_OBJ(camera);
        DELETE_OBJ(ecs);
    }

    void World::update(float delta)
    {
        camera->update(delta);
        ecs->updateSystem(motionSys, delta);
        ecs->updateSystem(arenaCollisionSys, delta);
    }

    void World::render(float alpha)
    {
        // Clear Screen
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // Set Renderer
        AmbientLight ambientLight(glm::vec3(0.05f));
        DirLight dirLight(glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        renderer->use();
        renderer->useCamera(camera);
        renderer->setAmbientLight(ambientLight);
        renderer->setDirLight(dirLight);
        renderer->setModelMat(glm::mat4(1.0f));
        
        // Draw Arena
        Material arenaMaterial(glm::vec3(0.0f, 0.7f, 0.2f));
        renderer->setMaterial(arenaMaterial);
        arenaMesh->use();
        arenaMesh->draw();

        ecs->updateSystem(ballRenderSys, alpha);

        window->swapBuffers();

        static double lastFrame = window->getTimer()->getTime();
        static double averageFps = 0.0;
        double thisFrame = window->getTimer()->getTime();
        averageFps += thisFrame - lastFrame;
        float tslf = static_cast<float>(thisFrame - lastFrame);
        lastFrame = thisFrame;
        static uint frameCount = 0;
        frameCount++;
        if (frameCount % 180 == 0) {
            std::cout << "Frame: " << frameCount << std::endl;
            std::cout << "FPS: " << 1.0f / tslf << std::endl;
            std::cout << "Average FPS: " << 1.0f/(averageFps / 180.0) << std::endl;
            std::cout << "BallCount: " << ballCount << std::endl;

            averageFps = 0.0;
        }
    }

    void World::addRandomBall()
    {
        glm::vec2 position;
        glm::vec2 velocity;
        float radius = Random::randomFloat(0.25f, 0.5f);
        float halfWidth = arenaWidth / 2.0f - radius;

        position.x = Random::randomFloat(-halfWidth, halfWidth);
        position.y = Random::randomFloat(-halfWidth, halfWidth);

        float maxSpeed = 5.0f;
        velocity.x = Random::randomFloat(-maxSpeed, maxSpeed);
        velocity.y = Random::randomFloat(-maxSpeed, maxSpeed);

        Material material(glm::vec3(Random::randomFloat(0.0f, 1.0f), 
            Random::randomFloat(0.0f, 1.0f), 
            Random::randomFloat(0.0f, 1.0f)));

        PositionComponent positionComp(position);
        MotionComponent motionComp(velocity);
        RadiusComponent radiusComp(radius);
        MaterialComponent materialComp(material);

        ecs->makeEntity(positionComp, motionComp, radiusComp, materialComp);
        ballCount++;
    }
}

