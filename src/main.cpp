/*
    Author: Marcus Porfilio
    Made for Linux Only
*/

#include <iostream>
#include <iomanip>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "Logger.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Object.h"
#include "render/Mesh.h"
#include "render/ModelLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "debugGame/DebugScene.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

bool wireframeMode = false;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


Camera cam = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(SCR_WIDTH, SCR_HEIGHT));
int width, height, nrChannels;

float lastX = SCR_WIDTH/2.0, lastY = SCR_HEIGHT/2.0;

bool firstMouse = true;



int main(){

    if(!glfwInit()){
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Oi", NULL, NULL);
    if(window == NULL){
        Logger("Window Creation failed.", true);
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK){
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);  

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    int fps = 0;

    DebugScene debugScene = DebugScene();
    debugScene.init();
    
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        fps = 1000/deltaTime;
        //Logger(std::to_string(fps).c_str(), false);
        

        //PROJECTION
        //Creating View Frustum Clipped from 0.1f to 100.0f and a 45deg FOV
        //projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);

        cam.loop(window, deltaTime);

        
        debugScene.update();
        debugScene.render(cam);

        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    debugScene.cleanUp();

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
} 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE && mods != GLFW_MOD_CONTROL){
        glfwSetWindowShouldClose(window, true);
    }
    if(key == GLFW_KEY_LEFT_ALT){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  
    }

    if(key == GLFW_KEY_X && action == GLFW_PRESS){
        if(!wireframeMode){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }else{
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        wireframeMode = !wireframeMode;
    }

    cam.processInput(key, action);

}


void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;

        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    cam.move(yoffset, xoffset);
}
