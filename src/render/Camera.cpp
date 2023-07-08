#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec2 resolution){
    pos = position;
    facing = target;
    direction = glm::normalize(pos-facing);
    globalUp = glm::vec3(0.0f, 1.0f, 0.0f);

    projection = glm::perspective(glm::radians(45.0f), (float)resolution.x/(float)resolution.y, 0.1f, 100.0f); //These values are fixed for now, may be accessible later.

    right = glm::normalize(glm::cross(globalUp, direction));
    up = glm::cross(direction, right);
    
    pitch = 0;
    yaw = -90.0f;

    glm::vec3 dir;

    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));

    front = glm::normalize(dir);
    view = glm::lookAt(pos, pos+front, globalUp);
}

void Camera::setPosFacing(glm::vec3 position, glm::vec3 target){
    pos = position;
    facing = target;
    direction = glm::normalize(pos-facing);

    view = glm::lookAt(pos, //Camera Position
            facing, //Target
            globalUp); //Up Vector, no real point in changing this.

    
}

void Camera::move(float pOffset, float yOffset){
    pitch += pOffset;
    yaw += yOffset;

    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) *  cos(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));

    front = glm::normalize(dir);
}

void Camera::loop(GLFWwindow *window, float deltaTime){
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        pos += speed * deltaTime * front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        pos -= speed * deltaTime * front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        pos -= glm::normalize(glm::cross(front, globalUp)) * speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        pos += glm::normalize(glm::cross(front, globalUp)) * speed * deltaTime;
    
    view = glm::lookAt(pos, pos+front, globalUp);
}

void Camera::processInput(int key, int action){
    /*if (key == GLFW_KEY_W && action == GLFW_PRESS)
        pos += speed * -direction;
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        pos -= speed * -direction;
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        pos -= glm::normalize(glm::cross(-direction, up)) * speed;
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        pos += glm::normalize(glm::cross(-direction, up)) * speed;*/
}