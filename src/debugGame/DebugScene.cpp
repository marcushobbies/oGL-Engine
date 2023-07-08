#include "debugGame/DebugScene.h"


void DebugScene::init(){
    maxObjectCount = 2;
    ambientLightStrength = 0.1f;

    ModelLoader loader;
    Mesh skullMesh = loader.loadObj("assets/Skull.obj");

    Object testObject = Object(glm::vec3(0.0f), glm::vec3(1.0f));
    testObject.initShaders(2, "assets/shaders/vertexShader.vs", "assets/shaders/fragmentShader.fs");
    testObject.initObject(skullMesh.getMesh(), skullMesh.getMeshSize(), skullMesh.getIndices(), skullMesh.getIndicesSize());
    testObject.initTextures(1, "assets/Skull.png");
    testObject.setScale(glm::vec3(0.8f));

    addObject(testObject);

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

    Mesh cubeMesh = loader.loadObj("assets/Cube.obj");

    Object testObject2 = Object(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f));
    testObject2.initShaders(2, "assets/shaders/vertexShader.vs", "assets/shaders/glowShader.fs");
    testObject2.initObject(cubeMesh);
    testObject2.initTextures(1, "assets/texture.png");
    testObject2.setScale(glm::vec3(0.2f));
    addObject(testObject2);

}
void DebugScene::update(){
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    objects[0].update();
    glm::vec3 newPos = objects[0].getPos();
    newPos.x = 2*sin((float)glfwGetTime()*3);
    newPos.z = 2*cos((float)glfwGetTime()*3);
    objects[0].setPos(newPos);

}