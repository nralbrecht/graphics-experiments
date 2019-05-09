#pragma once

#include <SFML/System/Vector3.hpp>

#include "IShape.h"
#include "ILoader.h"

class MeshShape : public IShape
{
private:
    std::vector<sf::Vector3f> normals;
    std::vector<sf::Vector3f> vertices;

    std::vector<unsigned int> indices;
    std::vector<unsigned int> normalIndices;

public:
    MeshShape(ILoader * loader);
    void Draw();
    void Translate(sf::Vector3f translation);
};
