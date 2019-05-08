#include <cmath>
#include <cstdio>
#include <iostream>

#include <SFML/OpenGL.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include "ILoader.h"
#include "MeshShape.h"

MeshShape::MeshShape(ILoader * loader) {
	indices = loader->GetIndices();
	vertices = loader->GetVertices();

    delete loader;

    std::cout << "vertices: " << vertices.size() << std::endl;
    std::cout << "indices:  " << indices.size() << std::endl;
}

void MeshShape::Draw() {
    glBegin(GL_TRIANGLES);
        // glColor3f(fillColor.x, fillColor.y, fillColor.z);

        for(auto const& index: indices) {
            const sf::Vector3f v = vertices.at(index);
            glVertex3f(v.x, v.y, v.z);
            glColor3f(v.x, v.y, v.z);
        }
    glEnd();
}

void MeshShape::Translate(sf::Vector3f translation) {
}
