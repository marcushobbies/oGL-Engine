#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

#include "Logger.h"

class Camera {
    public:
        Camera(glm::vec3 position, glm::vec3 target, glm::vec2 resolution);
        void setPosFacing(glm::vec3 position, glm::vec3 target);
        void move(float pOffset, float yOffset);
        void loop(GLFWwindow *window, float deltaTime);

        void processInput(int key, int action);

        glm::mat4 getView(){ return view; };
        glm::mat4 getProjection(){ return projection; };
        glm::vec3 getPos(){ return pos; };
        
    private:
        glm::vec3 pos, facing, direction, globalUp, up, right, front;
        glm::mat4 view, projection;
        float pitch, yaw;
        const float speed = 3.0f;

};