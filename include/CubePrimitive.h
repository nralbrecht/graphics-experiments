#pragma once

#include <vector>
#include <SFML/System/Vector3.hpp>

#include "IPrimitive.h"

class CubePrimitive : public IPrimitive
{
private:
    std::vector<int> indices;
    std::vector<sf::Vector3f> vertices;
    
public:
	sf::Vector3f fillColor;

    CubePrimitive(sf::Vector3f center);
    void Draw();
    void Translate(sf::Vector3f translation);
};
