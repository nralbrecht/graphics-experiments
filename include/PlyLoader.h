#pragma once

#include <vector>

#include <SFML/System/Vector3.hpp>

#include "ILoader.h"

class PlyLoader : public ILoader
{
private:
    std::vector<unsigned int> indices;
    std::vector<sf::Vector3f> vertices;

public:
    PlyLoader(const char* path);
    std::vector<unsigned int> GetIndices();
    std::vector<sf::Vector3f> GetVertices();
};
