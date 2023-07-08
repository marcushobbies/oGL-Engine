#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/Scene.h"
#include "Object.h"
#include "render/Mesh.h"
#include "render/ModelLoader.h"
#include "ShaderProgram.h"

class DebugScene : public Scene {

    public:
        void init() override;
        void update() override;
        //TODO: See Scene.h
    private:
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

};