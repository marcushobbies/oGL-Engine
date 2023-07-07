#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Logger.h"

class ShaderProgram {
    public:
        ShaderProgram();
        void generateProgram();
        //TYPES: .vs - Vertex shader, .fs - Fragment shade, .cs - Compute Shader
        [[deprecated("Replaced by loadShader(const char* path), only remains for debug purposes.")]]
        void loadShader(const char* path, int type);
        void loadShader(const char* path);
        void attachShaders();
        int getProgramId() {return programId;};
        std::vector<int> getShaderIds() {return shaderIds;};

        void setInt(const char* name, int val) const;
        void setFloat(const char* name, float val) const;
        void setVec3(const char* name, float x, float y, float z) const;
        void setVec4(const char* name, float x, float y, float z, float w) const;
        void setMatrix4f(const char* name, GLfloat* val) const;
    private:
        int programId = 0;
        std::vector<int> shaderIds;
        std::vector<GLchar*> shaderSources;

        const std::string extensions[2] = {".vs", ".fs"};
        const int extensionTypes[2] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
};