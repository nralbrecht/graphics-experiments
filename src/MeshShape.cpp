#include <cmath>
#include <cstdio>
#include <iostream>

#include <SFML/OpenGL.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include "ILoader.h"
#include "MeshShape.h"

MeshShape::MeshShape(ILoader * loader) {
    normals = loader->GetNormals();
    vertices = loader->GetVertices();

    indices = loader->GetIndices();
    normalIndices = loader->GetNormalIndices();

    delete loader;
}

void MeshShape::Draw() {
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 1.0f, 0.0f);

        for (int i = 0; i < indices.size(); ++i) {
            const sf::Vector3f vertex = vertices.at(indices.at(i));

            if (indices.size() == normalIndices.size()) {
                const sf::Vector3f normal = normals.at(normalIndices.at(i));
                glColor3f(normal.x, normal.y, normal.z);
            }
            else {
                glColor3f(vertex.x, vertex.y, vertex.z);
            }

            glVertex3f(vertex.x, vertex.y, vertex.z);
        }
    glEnd();
}

void MeshShape::Translate(sf::Vector3f translation) {
}
