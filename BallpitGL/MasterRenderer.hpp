#pragma once

// Includes
#include "UppIncludes.hpp"

// Forward Declarations
namespace upp
{
    class Camera;
    class Shader;
    struct Material;
    struct DirLight;
    struct AmbientLight;
}

namespace upp
{
    class MasterRenderer
    {
    public:
        MasterRenderer();

        void initialize();
        void shutdown();

        void use();
        void useCamera(Camera* cam);
        void setModelMat(glm::mat4& modelMat);
        void setVPMat(glm::mat4& vpMat);

        void setMaterial(const Material& material);
        void setDirLight(const DirLight& dirLight);
        void setAmbientLight(const AmbientLight& ambient);

        // Fun Stuff
        void toggleThroughPolygonModes();

    private:
        void loadUniformLocations();
        void setOpenGlParams();

    private:
        Shader* masterShader;

        // Vertex Uniforms
        int loc_modelMat;
        int loc_vpMat;
        // Fragment Uniforms
        int loc_material_color;
        int loc_dirLight_dir;
        int loc_dirLight_color;
        int loc_ambientLight;
    };
}