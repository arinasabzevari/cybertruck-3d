//Arina Sabzevari (40205861)
//Parsa Ghadimi (40203370)
//Zineb Alaoui Aziz (40215844)

#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <vector>
#include <glm/glm.hpp>

bool loadOBJ(const char* path, std::vector<glm::vec3>& out_vertices, std::vector<unsigned int>& out_indices);

#endif
