#pragma once

#include <glm/glm.hpp>

#include "engine/Light.h"
#include "Object.h"
#include "Camera.h"
#include "render/Mesh.h"
#include "render/ModelLoader.h"

class LightDebugObject : public Object{
    public:
        LightDebugObject(Light* light);
        void init(Light* light);
        void render(glm::mat4 view_, glm::mat4 projection_) override;
        void update() override;
        void updatePos(glm::vec3 position);
    private:
        Light* targetLight;
        ModelLoader loader;
        Mesh debugMesh;

};