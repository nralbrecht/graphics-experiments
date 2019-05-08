#pragma once

#include <SFML/System/Vector3.hpp>

#include "IShape.h"
#include "ILoader.h"

class MeshShape : public IShape
{
private:
    std::vector<unsigned int> indices;
    std::vector<sf::Vector3f> vertices;

public:
    MeshShape(ILoader * loader);
    void Draw();
    void Translate(sf::Vector3f translation);
};
