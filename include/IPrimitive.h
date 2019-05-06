#pragma once

#include <SFML/System/Vector3.hpp>

class IPrimitive
{
public:
    virtual void Draw() = 0;
    virtual void Translate(sf::Vector3f translation) = 0;
};
