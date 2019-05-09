#pragma once

#include <vector>

#include <SFML/System/Vector3.hpp>

#include "ILoader.h"

class ObjLoader : public ILoader
{
private:
    std::vector<sf::Vector3f> normals;
    std::vector<sf::Vector3f> vertices;

    std::vector<unsigned int> indices;
    std::vector<unsigned int> normalIndices;

public:
    ObjLoader(const char* path);
    std::vector<sf::Vector3f> GetNormals();
    std::vector<sf::Vector3f> GetVertices();
    
    std::vector<unsigned int> GetIndices();
    std::vector<unsigned int> GetNormalIndices();
};
