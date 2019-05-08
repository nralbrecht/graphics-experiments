#include <cmath>
#include <cstdio>

#include <SFML/OpenGL.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <delabella.h>

#include <SphereShape.h>

SphereShape::SphereShape(int points, sf::Vector3f center, float radius) {
    fillColor = sf::Vector3f(0.0f, 1.0f, 0.f);

    std::vector<sf::Vector2f> projection;
    for (int i = 0; i < points; ++i) {
        float phi = std::acos(1.0f - 2.0f * (i + 0.5f) / points);
        float theta = M_PI * (1 + sqrt(5)) * (i + 0.5f);
        
        float x = std::cos(theta) * std::sin(phi);
        float y = std::sin(theta) * std::sin(phi);
        float z = std::cos(phi);
        
        vertices.push_back(sf::Vector3f(x, y, z));
        projection.push_back(sf::Vector2f(x / (1 - z), y / (1 - z)));
    }

    IDelaBella* idb = IDelaBella::Create();

    // int verts = idb->Triangulate(points, &vertices[0].x, &vertices[0].y, sizeof(sf::Vector2f));
    int verts = idb->Triangulate(points, &projection[0].x, &projection[0].y, sizeof(sf::Vector2f));

    if (verts > 0) {
        int tris = verts / 3;
        const DelaBella_Triangle* dela = idb->GetFirstDelaunayTriangle();
        for (int i = 0; i < tris; i++) {
            indices.push_back(dela->v[0]->i);
            indices.push_back(dela->v[1]->i);
            indices.push_back(dela->v[2]->i);

            dela = dela->next;
        }
    }
    else {
        printf("could not triangulate: %d\n", verts);
    }

    idb->Destroy();

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(4);
}

void SphereShape::Draw() {
    glBegin(GL_TRIANGLES);
        // glColor3f(fillColor.x, fillColor.y, fillColor.z);
        for(auto const& index: indices) {
            const sf::Vector3f v = vertices.at(index);
            glVertex3f(v.x, v.y, v.z);
            glColor3f(v.x, v.y, v.z);
        }
    glEnd();
}

void SphereShape::Translate(sf::Vector3f translation) {
}
