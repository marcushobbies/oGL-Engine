
#include <iostream>
#include <iomanip>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <string>

#include "Logger.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Object.h"
#include "render/Mesh.h"
#include "render/ModelLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

bool wireframeMode = false;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


Camera cam = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f));
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
    //RENDERING CODE

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };


glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};


    //Data pulled from a default cube exported in .obj format in Blender with triangulated faces.
    float verticesEBO[] = {
        1.0, 1.0, -1.0,      1.0, 1.0,  //0
        1.0, -1.0, -1.0,     1.0, 1.0,  //1
        1.0, 1.0, 1.0,       1.0, 1.0,  //2
        1.0, -1.0, 1.0,      1.0, 1.0,  //3
        -1.0, 1.0, -1.0,     1.0, 1.0,  //4
        -1.0, -1.0, -1.0,    1.0, 1.0,  //5
        -1.0, 1.0, 1.0,      1.0, 1.0,  //6
        -1.0, -1.0, 1.0,     1.0, 1.0,  //7
    };
    unsigned int indicesEBO[] = { 
        4, 2, 0,
        2, 7, 3,
        6, 5, 7,
        1, 7, 5,
        0, 3, 1,
        4, 1, 5,
        4, 6, 2,
        2, 6, 7,
        6, 4, 5,
        1, 3, 7,
        0, 2, 3,
        4, 0, 1
    };  

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    
    ModelLoader loader;
    Mesh mesh = loader.loadObj("models/Test.obj");
    std::cout << std::fixed;
    std::cout << std::setprecision(3);
    /*for(int i = 0; i < mesh.getMeshSize()/sizeof(float[1]); i++){
        if(i % 5 == 0){
            std::cout << std::endl;
        }

        std::cout << mesh.getMesh()[i] << ", ";
    }
    std::cout << std::endl;*/
    //std::cout << sizeof(indicesEBO) << " vs " << (36*sizeof(unsigned int[1])) << std::endl;

    Object testObject = Object(glm::vec3(0.0f), glm::vec3(0.0f));
    testObject.initShaders(2, "shaders/vertexShader.vs", "shaders/fragmentShader.fs");
    //testObject.initObject(verticesEBO, sizeof(verticesEBO), indicesEBO, sizeof(indicesEBO));
    testObject.initObject(mesh.getMesh(), mesh.getMeshSize(), mesh.getIndices(), mesh.getIndicesSize());
    testObject.initTextures(2, "texture.png", "Smiley.png");

    Object testObject2 = Object(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f));
    testObject2.initShaders(2, "shaders/vertexShader.vs", "shaders/fragmentShader.fs");
    testObject2.initObject(vertices, sizeof(vertices));
    testObject2.initTextures(1, "texture.png");


    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    int fps = 0;

    /*glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);*/
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        fps = 1000/deltaTime;
        //Logger(std::to_string(fps).c_str(), false);
        //Vertex coords -> World Coords
        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        //World Coords -> View Coords
        //glm::mat4 view = glm::mat4(1.0f);
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); //Moving the whole scene back 3.0f
            //PROJECTION
            //Creating View Frustum Clipped from 0.1f to 100.0f and a 45deg FOV
        
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);

        view = cam.getView();
        cam.loop(window, deltaTime);

        //haderProgram.setMatrix4f("view", glm::value_ptr(view));
        //shaderProgram.setMatrix4f("projection", glm::value_ptr(projection));





        testObject.render(view, projection);
        testObject.update();

        testObject2.render(view, projection);
        testObject2.update();
        glm::vec3 newPos = testObject2.getPos();
        newPos.x = 2*sin((float)glfwGetTime()*3);
        newPos.z = 2*cos((float)glfwGetTime()*3);

        testObject2.setPos(newPos);

        /*glBindVertexArray(VAO);
        glUseProgram(shaderProgram.getProgramId());

        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = (i % 3 == 0) ? (float)glfwGetTime()*25.0f : 20.0f * i; 
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shaderProgram.setMatrix4f("model", glm::value_ptr(model));
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }
            //glm::mat4 model = glm::mat4(1.0f);
            //model = glm::translate(model, glm::vec3(0.0, 0.19, 0.2));
            //shaderProgram.setMatrix4f("model", glm::value_ptr(model));
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        std::cout << glGetError() << std::endl;*/

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[1]);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    testObject.cleanUp();
    testObject2.cleanUp();
    //glDeleteProgram(shaderProgram.getProgramId());

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
