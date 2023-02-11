#pragma once

#include "Vertex.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

class Mesh {
    public:
        void addVertex(Vertex vertex);
        void addFace(Face face);
        void addIndice(unsigned int index);
        void addVertexTextureCoords(int index, glm::vec2 texCoords);

        void establishArrays();

        float* getMesh(){ return mesh; };
        size_t getMeshSize(){ return meshSize; };
        unsigned int* getIndices(){ return indices; };
        size_t getIndicesSize(){ return indicesSize; };

        Vertex getVertex(int index){ return vertices[index]; };

    private:
        std::vector<Vertex> vertices;
        std::vector<Face> faces;

        std::vector<float> workingMesh;
        std::vector<unsigned int> workingIndices;

        float* mesh;
        size_t meshSize = 0;

        unsigned int* indices;
        size_t indicesSize;
};