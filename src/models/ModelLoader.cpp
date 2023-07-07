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
        std::vector<glm::vec3> plainNormals;
        std::vector<glm::vec2> plainTextureCoordinates;

        std::string line;
        int numVertices = 0;
        while(getline(model, line)){
            if(line[0] == '#'){
                continue;
            }

            /*
            The split "Data Groups" from an obj file. 
            The first part of the group (dataGroups[0]) will always determine what the following data is used for, either a
            geometric vertex (v), face (f), texture coordinate (vt), normal (vn) or parameter space vertice (vp).
            These may either contain a single number or an array of numbers split by '/' in the case of faces. (Ex: 0.625 or 7/11/3) 
            */
            std::vector<std::string> dataGroups = splitString(line, ' '); 

            if(dataGroups[0] == "v"){
                Vertex workingVertex = {};

                plainVertices.push_back(std::stof(dataGroups[1]));
                plainVertices.push_back(std::stof(dataGroups[2]));
                plainVertices.push_back(std::stof(dataGroups[3]));
                workingVertex.position.x = std::stof(dataGroups[1]);
                workingVertex.position.y = std::stof(dataGroups[2]);
                workingVertex.position.z = std::stof(dataGroups[3]);

                loadedMesh.addVertex(workingVertex);
            }
            if(dataGroups[0] == "vn"){
                plainNormals.push_back(glm::vec3(std::stof(dataGroups[1]), std::stof(dataGroups[2]), std::stof(dataGroups[3])));
            }
            if(dataGroups[0] == "vt"){
                plainTextureCoordinates.push_back(glm::vec2(std::stof(dataGroups[1]), std::stof(dataGroups[2])));
            }
            //SWITCH TO INDICES MODE, Start using the Vertex class. This must always be done last.
            if(dataGroups[0] == "f"){
                Face face = {};
                int currentVertex = 0;
                for(std::string p : dataGroups){
                    if(p == "f"){
                        continue;
                    }
                    std::vector<std::string> sf = splitString(p, '/');
                    long vertexIndice = std::stol(sf[0])-1;
                    long textureIndice = std::stol(sf[1])-1;
                    long normalIndice = std::stol(sf[2])-1;   //Todo: Implement Normals, this is ignored for now.
                    
                    Vertex modifiedVertex = loadedMesh.getVertex(vertexIndice);
                    modifiedVertex.textureCoords = plainTextureCoordinates[textureIndice];
                    modifiedVertex.normal = plainNormals[normalIndice];

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

