#include "render/Mesh.h"

void Mesh::addVertex(Vertex vertex){
    vertices.push_back(vertex);
}

void Mesh::addFace(Face face){
    faces.push_back(face);
}

void Mesh::addIndice(unsigned int index){
    workingIndices.push_back(index);
}


void Mesh::addVertexTextureCoords(int index, glm::vec2 texCoords){
    //vertices[index].textureCoords.push_back(texCoords);
    vertices[index].textureCoords = texCoords;
}


void Mesh::establishArrays(){
    /*for(Vertex v : vertices){
            workingMesh.push_back(v.position.x);
            workingMesh.push_back(v.position.y);
            workingMesh.push_back(v.position.z);
            workingMesh.push_back(v.textureCoords.x);
            workingMesh.push_back(v.textureCoords.y);


        //NORMALS ARE NOT INCLUDED IN THIS ARRAY YET
    }*/
    int indice = 0;
    for(Face f : faces){
        //std::cout << "f" << std::endl;
        for(Vertex v : f.vertices){
            //std::cout << "v " << v.position.x << ", " << v.position.y << ", " << v.position.z << ", " << v.textureCoords.x << ", " << v.textureCoords.y << std::endl;
            workingMesh.push_back(v.position.x);
            workingMesh.push_back(v.position.y);
            workingMesh.push_back(v.position.z);
            workingMesh.push_back(v.textureCoords.x);
            workingMesh.push_back(v.textureCoords.y);

            addIndice(indice);
            indice++;
        }
    }

    mesh = new float[workingMesh.size()];
    std::copy(workingMesh.begin(), workingMesh.end(), mesh);
    meshSize = workingMesh.size()*sizeof(float);

    std::cout << std::fixed;
    std::cout << std::setprecision(3);
    /*for(int i = 0; i < workingMesh.size(); i++){
        if(i % 5 == 0){
            std::cout << std::endl;
        }

        std::cout << workingMesh[i] << ", ";
    }
    std::cout << std::endl;*/


    indices = new unsigned int[workingIndices.size()];
    std::copy(workingIndices.begin(), workingIndices.end(), indices);
    indicesSize = workingIndices.size()*sizeof(unsigned int);
}