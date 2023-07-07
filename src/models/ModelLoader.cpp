#include "render/ModelLoader.h"

std::vector<std::string> ModelLoader::splitString(std::string input, const char separator){
    std::stringstream l(input);
    std::string value;
    std::vector<std::string> output;
    while(getline(l, value, separator)){
        output.push_back(value);
    }
    return output;
}

// The models loaded with this must have triangulated faces.
Mesh ModelLoader::loadObj(const char* filePath){
    Mesh loadedMesh;
    std::ifstream model(filePath);
    
    if(model.is_open()){
        std::vector<float> plainVertices;
        std::vector<float> plainNormals;
        std::vector<glm::vec2> plainTextureCoordinates;

        std::string line;
        int numVertices = 0;
        while(getline(model, line)){
            if(line[0] == '#'){
                continue;
            }

            std::vector<std::string> ss = splitString(line, ' ');
            if(ss[0] == "v"){
                Vertex workingVertex = {};

                plainVertices.push_back(std::stof(ss[1]));
                plainVertices.push_back(std::stof(ss[2]));
                plainVertices.push_back(std::stof(ss[3]));
                workingVertex.position.x = std::stof(ss[1]);
                workingVertex.position.y = std::stof(ss[2]);
                workingVertex.position.z = std::stof(ss[3]);

                loadedMesh.addVertex(workingVertex);
            }
            if(ss[0] == "vn"){
                plainNormals.push_back(std::stof(ss[1]));
                plainNormals.push_back(std::stof(ss[2]));
                plainNormals.push_back(std::stof(ss[3]));
            }
            if(ss[0] == "vt"){
                plainTextureCoordinates.push_back(glm::vec2(std::stof(ss[1]), std::stof(ss[2])));
            }
            //SWITCH TO INDICES MODE, Start using the Vertex class. This must always be done last.
            if(ss[0] == "f"){
                Face face = {};
                int currentVertex = 0;
                for(std::string p : ss){
                    if(p == "f"){
                        continue;
                    }
                    std::vector<std::string> sf = splitString(p, '/');
                    long vertexIndice = std::stol(sf[0])-1;
                    long textureIndice = std::stol(sf[1])-1;
                    long normalIndice = std::stol(sf[2])-1;   //Todo: Implement Normals, this is ignored for now.
                    
                    Vertex modifiedVertex = loadedMesh.getVertex(vertexIndice);
                    modifiedVertex.textureCoords = plainTextureCoordinates[textureIndice];

                    face.vertices[currentVertex] = modifiedVertex;

                    //loadedMesh.addVertexTextureCoords(vertexIndice, plainTextureCoordinates[textureIndice]);

                    //workingVertex.normal.x = plainNormals[normalIndice];
                    //workingVertex.normal.y = plainNormals[normalIndice+1];
                    //workingVertex.normal.z = plainNormals[normalIndice+2];

                    //std::cout << workingVertex.position.x << ", " << workingVertex.position.y << ", " << workingVertex.position.z << ", " << workingVertex.textureCoords.x << ", " << workingVertex.textureCoords.y << std::endl;

                    //loadedMesh.addIndice(vertexIndice);
                    currentVertex++;
                }
                loadedMesh.addFace(face);
            }
        }

        model.close();
    }
    loadedMesh.establishArrays();
    return loadedMesh;
}

