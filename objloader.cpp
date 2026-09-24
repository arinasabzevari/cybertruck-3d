//Arina Sabzevari (40205861)
//Parsa Ghadimi (40203370)
//Zineb Alaoui Aziz (40215844)

#include "objloader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

bool loadOBJ(const char* path, std::vector<glm::vec3>& out_vertices, std::vector<unsigned int>& out_indices) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Cannot open OBJ file: " << path << std::endl;
        return false;
    }

    std::vector<glm::vec3> temp_vertices;
    std::vector<unsigned int> temp_indices;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            float x, y, z;
            ss >> x >> y >> z;
            temp_vertices.push_back(glm::vec3(x, y, z));
        } else if (prefix == "f") {
            std::vector<unsigned int> faceIndices;
            std::string vertexStr;

            // Supports face lines like: f 1/1/1 2/2/1 3/3/1 4/4/1
            while (ss >> vertexStr) {
                std::istringstream vs(vertexStr);
                std::string vIdx;
                std::getline(vs, vIdx, '/');  // Only extract vertex index before first '/'
                try {
                    int index = std::stoi(vIdx);
                    faceIndices.push_back(index - 1); // Convert to 0-based indexing
                } catch (...) {
                    std::cerr << "Error parsing face index: " << vertexStr << std::endl;
                }
            }

            // Triangulate: (0,1,2), (0,2,3), ...
            for (size_t i = 1; i + 1 < faceIndices.size(); ++i) {
                temp_indices.push_back(faceIndices[0]);
                temp_indices.push_back(faceIndices[i]);
                temp_indices.push_back(faceIndices[i + 1]);
            }
        }
    }

    out_vertices = temp_vertices;
    out_indices = temp_indices;
    return true;
}
