#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include "render/Vertex.h"
#include "render/Mesh.h"
#include "Logger.h"

class ModelLoader{
    public:
        Mesh loadObj(const char* filePath);
        std::vector<std::string> splitString(std::string input, const char separator);
};