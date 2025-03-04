#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string.h>
#include <stdarg.h>
#include <sstream>
#include <string.h>
#include <vector>

#include "Logger.h"
#include "ShaderProgram.h"
#include "stb_image.h"
#include "Camera.h"
#include "render/Mesh.h"
#include "engine/Light.h"

class Object{
    public:
        Object();
        Object(glm::vec3 position, glm::vec3 rotation);

        void initObject(float vertices[], size_t size);
        void initObject(float vertices[], size_t verticesSize, unsigned int indices[], size_t indicesSize);
        void initObject(Mesh mesh);
        void initShaders(unsigned int shaders, ...);
        void initTextures(unsigned int textures, ...);
        
        void calculateLightingFromScene(Camera camera, float ambientLightStrength, std::vector<Light> lights, int numberOfLights);

        virtual void update();
        virtual void render(glm::mat4 view_, glm::mat4 projection_);

        void cleanUp();
        
        void setPos(glm::vec3 position){ pos = position; };
        void setRot(glm::vec3 rotation, float angle){ rot = rotation; angle_= angle; };
        void setScale(glm::vec3 scale){ scale_ = scale; };

        glm::vec3 getPos(){return pos;};        
        glm::vec3 getRot(){return rot;};
        glm::vec3 getScale(){return scale_;};  
  
        unsigned int getVBO(){return VBO;};
        unsigned int getEBO(){return EBO;};
        unsigned int getVAO(){return VAO;};

    protected:
        float angle_;
        glm::vec3 pos, rot, scale_;
        glm::mat4 model, projection, view;
        ShaderProgram shaderProgram;
        GLuint VBO, EBO, VAO;

        float *verts;
        unsigned int *inds;
        size_t vertsSize, indSize;
        unsigned int texture[2];
        unsigned int textureCount;
        
        bool usingEBO = false;
};