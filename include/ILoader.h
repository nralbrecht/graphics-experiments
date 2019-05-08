#pragma once
#include <vector>

#include <SFML/System/Vector3.hpp>

class ILoader
{
public:
    virtual ~ILoader() {}
    virtual std::vector<sf::Vector3f> GetVertices() = 0;
    virtual std::vector<unsigned int> GetIndices() = 0;
};
