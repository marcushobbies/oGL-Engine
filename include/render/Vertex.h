#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Vertex{
        glm::vec3 position;
        glm::vec2 textureCoords; /*ToDo: Multiple texture coordinates, maybe have a vector of 
                                texture coords that causes the vertex to be duplicated when 
                                the mesh is established?
                                The indices would need to then be re-written appropriately though.
                                You would need to duplicate a vertex for every face it's on.
                                */
        glm::vec3 normal;
};

struct Face {
    public:
        Vertex vertices[3];
};