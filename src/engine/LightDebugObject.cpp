#include "engine/LightDebugObject.h"

LightDebugObject::LightDebugObject(Light* light){
    targetLight = light;
    
    angle_ = 0;

    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);

    initShaders(2, "assets/shaders/lightSourceShader.vs", "assets/shaders/lightSourceShader.fs");
    glUseProgram(shaderProgram.getProgramId());
    shaderProgram.setVec3("lightColour", light->colour);

    debugMesh = loader.loadObj("assets/Cube.obj");
    initObject(debugMesh);

    setScale(glm::vec3(0.1f));

}

void LightDebugObject::init(Light* light){
    targetLight = light;

    initShaders(2, "assets/shaders/lightSourceShader.vs", "assets/shaders/lightSourceShader.fs");
}

void LightDebugObject::update(){
    pos = targetLight->position;
}

void LightDebugObject::updatePos(glm::vec3 position){
    pos = position;
}


void LightDebugObject::render(glm::mat4 view_, glm::mat4 projection_){
    view = view_;
    projection = projection_;

    glBindVertexArray(VAO);
    glUseProgram(shaderProgram.getProgramId());

    model = glm::translate(glm::mat4(1.0f), pos);
    model = glm::rotate(model, glm::radians(angle_), rot);
    model = glm::scale(model, scale_);

    shaderProgram.setMatrix4f("model", glm::value_ptr(model));
    shaderProgram.setMatrix4f("view", glm::value_ptr(view));
    shaderProgram.setMatrix4f("projection", glm::value_ptr(projection));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, indSize/sizeof(unsigned int[1]), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}
