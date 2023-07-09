#pragma once

#include <vector>

#include "render/Mesh.h"
#include "Object.h"
#include "Camera.h"
#include "engine/Light.h"
#include "engine/LightDebugObject.h"

class Scene {
    public:

        Scene();

        unsigned long addObject(Object object);

        virtual void init();
        virtual void render(Camera camera); //TODO: Render multiple lights, have them processed mostly by the scene somehow and done in the shaders so each object doesn't have to call every light source.
        virtual void update();

        void cleanUp();

    private:
        unsigned long currentObjectCount;

    protected:
        std::vector<Object> objects;
        std::vector<Light> lights;
        std::vector<LightDebugObject> lightDebugObjects;

        unsigned long maxObjectCount;
        float ambientLightStrength;

        const bool drawLightObjects = true;
};