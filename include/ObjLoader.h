#pragma once

#include <vector>

#include <SFML/System/Vector3.hpp>

#include "ILoader.h"

class ObjLoader : public ILoader
{
private:
    std::vector<unsigned int> indices;
    std::vector<sf::Vector3f> normals;
    std::vector<sf::Vector3f> vertices;

public:
    ObjLoader(const char* path);
    std::vector<unsigned int> GetIndices();
    std::vector<unsigned int> GetNormals();
    std::vector<sf::Vector3f> GetVertices();
};
