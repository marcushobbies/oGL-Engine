#include "Object.h"

Object::Object(glm::vec3 position, glm::vec3 rotation){
    pos = position;
    rot = rotation;
    scale_ = glm::vec3(1.0f);
    angle_ = 0;

    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);


}

void Object::initObject(float vertices[], size_t size){
    verts = vertices;
    vertsSize = size;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO); 

    glBindVertexArray(VAO);

    //Since this command is alone, make sure the program has set the state to the right VAO BEFORE creating an object.
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Binding VBO0 to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); //Binding data to GL_ARRAY BUFFER

    int32_t bsize = 0;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bsize);

    // Check if buffer is empty.
    std::stringstream output;
    output << bsize;
    Logger(output.str().c_str(), false);
    

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); //Appending data into the vertex shader at location = 0
    glEnableVertexAttribArray(0);  

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float))); //Texture data at location = 1
    glEnableVertexAttribArray(1);

    //Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}


void Object::initObject(float vertices[], size_t verticesSize, unsigned int indices[], size_t indicesSize){
    verts = vertices;
    vertsSize = verticesSize;
    inds = indices;
    indSize = indicesSize;
    usingEBO = true;

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO); 

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW); //Binding data to GL_ARRAY BUFFER

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    int32_t bsize = 0;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bsize);

    // Check if buffer is empty.
    std::stringstream output;
    output << bsize;
    Logger(output.str().c_str(), false);
    

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //Appending data into the vertex shader at location = 0
    glEnableVertexAttribArray(0);  

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float))); //Texture data at location = 1
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float))); //Normal data at location = 2
    glEnableVertexAttribArray(2);

    //Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}

void Object::initShaders(unsigned int shaders, ...){
    shaderProgram.generateProgram();
    va_list shaderPaths;
    va_start(shaderPaths, shaders);
    for(int i = 0; i < shaders; i++){
        shaderProgram.loadShader(va_arg(shaderPaths, const char*));
    }
    va_end(shaderPaths);

    shaderProgram.attachShaders();

}

//Ex: init(3, path1, path2, path3)
void Object::initTextures(unsigned int textures, ...){
    stbi_set_flip_vertically_on_load(true);

    glBindVertexArray(VAO);

    unsigned int textureIds[2];

    va_list paths;
    va_start(paths, textures);
    glGenTextures(textures, texture); //#textures, textureIds 

    for(int i = 0; i < textures; i++){
        //Logger(va_arg(paths, const char*), false);
        int texWidth, texHeight, nrChannels;
            unsigned char* textureData; 

        glBindTexture(GL_TEXTURE_2D, texture[i]);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glUseProgram(shaderProgram.getProgramId());

        const char* cTPath = va_arg(paths, const char*);

        textureData = stbi_load(cTPath, &texWidth, &texHeight, &nrChannels, 0);
        if(textureData){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
            glGenerateMipmap(GL_TEXTURE_2D);
            std::string textureUniformName = "texture" + std::to_string(i);
            shaderProgram.setInt(textureUniformName.c_str(), i);

            //std::string gMsg = "Loaded texture at uniform ";
            //gMsg += textureUniformName;
            //Logger(gMsg.c_str());
        }else{
            std::string errorMsg = "Failed to load texture at ";
            //errorMsg += *cTPath; //Segmentation Fault. 
            errorMsg += std::to_string(i);
            Logger(errorMsg.c_str(), true);
        }
        stbi_image_free(textureData);

    }
    va_end(paths);

    //texture = textureIds;
    textureCount = textures;

    calculateLightingFromScene(); //Debug code, should be called by the scene which the object is in whenever lighting conditions change, at the moment scenes are not implemented.

    glBindVertexArray(0);
}

void Object::calculateLightingFromScene(){
    //Ambient Scene Lighting, to be determined by a scene's skybox
    float ambientLightStrength = 0.0f;
    shaderProgram.setVec3("ambientLightColor", ambientLightStrength, ambientLightStrength, ambientLightStrength);
    //Temporary Light source position
    shaderProgram.setVec3("lightPos", 0.0f, 0.0f, 0.0f);
    shaderProgram.setVec3("lightColor", 1.0f, 0.0f, 1.0f);


}

void Object::update(){

}

void Object::render(glm::mat4 view_, glm::mat4 projection_){
    view = view_;
    projection = projection_;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);       //DEBUG CODE

    glBindVertexArray(VAO);
    glUseProgram(shaderProgram.getProgramId());


    model = glm::translate(glm::mat4(1.0f), pos);
    model = glm::rotate(model, glm::radians(angle_), rot);
    model = glm::scale(model, scale_);
    shaderProgram.setMatrix4f("model", glm::value_ptr(model));

    shaderProgram.setMatrix4f("view", glm::value_ptr(view));
    shaderProgram.setMatrix4f("projection", glm::value_ptr(projection));

    if(usingEBO) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, indSize/sizeof(unsigned int[1]), GL_UNSIGNED_INT, 0);
    }else{
        glBindBuffer(GL_VERTEX_ARRAY, VBO);
        glDrawArrays(GL_TRIANGLES, 0, vertsSize/sizeof(float[1])/5);
    }
    

    glBindVertexArray(0);
}

void Object::cleanUp(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram.getProgramId());

}