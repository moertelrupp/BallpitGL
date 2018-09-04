#include "MasterRenderer.hpp"

// Prevent circular Dependencies
#include "Shader.hpp"
#include "Camera.hpp"
#include "LightingData.hpp"

namespace upp
{
    MasterRenderer::MasterRenderer()
    {
        masterShader = nullptr;
        loc_modelMat = -1;
        loc_vpMat = -1;
    }

    void MasterRenderer::initialize()
    {
        masterShader = new Shader("master.vert", "master.frag");
        loadUniformLocations();
        setOpenGlParams();
    }

    void MasterRenderer::shutdown()
    {
        if (masterShader)
        {
            delete masterShader;
            masterShader = nullptr;
        }
    }

    void MasterRenderer::use()
    {
        masterShader->use();
    }

    void MasterRenderer::useCamera(Camera* cam)
    {
        glm::mat4 view = cam->calcView();
        glm::mat4 projection = cam->calcProjection();
        glm::mat4 vpMat = projection * view;

        masterShader->setUniformMat4f(loc_vpMat, vpMat);
    }

    void MasterRenderer::setModelMat(glm::mat4& modelMat)
    {
        masterShader->setUniformMat4f(loc_modelMat, modelMat);
    }

    void MasterRenderer::setVPMat(glm::mat4& vpMat)
    {
        masterShader->setUniformMat4f(loc_vpMat, vpMat);
    }

    void MasterRenderer::setMaterial(const Material& material)
    {
        masterShader->setUniformVec3f(loc_material_color, material.color);
    }

    void MasterRenderer::setDirLight(const DirLight& dirLight)
    {
        masterShader->setUniformVec3f(loc_dirLight_color, dirLight.color);
        masterShader->setUniformVec3f(loc_dirLight_dir, dirLight.dir);
    }

    void MasterRenderer::setAmbientLight(const AmbientLight& ambient)
    {
        masterShader->setUniformVec3f(loc_ambientLight, ambient.color);
    }

    void MasterRenderer::loadUniformLocations()
    {
        // Vertex Uniforms
        loc_modelMat = masterShader->getUniformLoc("modelMat");
        loc_vpMat = masterShader->getUniformLoc("vpMat");

        // Fragment Uniforms
        loc_material_color = masterShader->getUniformLoc("material.color");
        loc_dirLight_color = masterShader->getUniformLoc("dirLight.color");
        loc_dirLight_dir = masterShader->getUniformLoc("dirLight.dir");
        loc_ambientLight = masterShader->getUniformLoc("ambientLight");
    }

    void MasterRenderer::setOpenGlParams()
    {
        glClearColor(66.0f / 256.0f, 134.0f / 256.0f, 244.0f / 256.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        glEnable(GL_PROGRAM_POINT_SIZE);
        glPointSize(3.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void MasterRenderer::toggleThroughPolygonModes()
    {
        static uint counter = 2;
        counter = (counter + 1) % 3;
        if (counter == 2)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        else if (counter == 1)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else if (counter == 0)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        }
    }
}
