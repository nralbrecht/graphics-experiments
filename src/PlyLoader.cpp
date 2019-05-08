#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>
#include <delabella.h>

#include "PlyLoader.h"

PlyLoader::PlyLoader(const char* path) {
    std::ifstream is(path);
    
    int lineNumber = 0;
    bool inHeader = true;

    int remainingIndices = 0;
    int remainingVertices = 0;

    std::string line;
    while(std::getline(is, line)) {
        lineNumber++;
        
        if (inHeader) {
            if (line.substr(0,7) == "element") {
                std::istringstream iss(line);
                std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                        std::istream_iterator<std::string>());

                if (results.at(1) == "vertex") {
                    remainingVertices = std::stoi(results.at(2));
                }
                if (results.at(1) == "range_grid") {
                    remainingIndices = std::stoi(results.at(2));
                }
            }
            else if (line.substr(0,10) == "end_header") {
                inHeader = false;
            }
        }
        else {
            if (remainingVertices > 0) {
                std::istringstream iss(line);
                std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                        std::istream_iterator<std::string>());

                vertices.push_back(
                    sf::Vector3f(std::stof(results.at(0)), std::stof(results.at(1)), std::stof(results.at(2))));

                remainingVertices--;
            }
            else if (remainingIndices > 0) {
                std::istringstream iss(line);
                std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                        std::istream_iterator<std::string>());

                if (results.at(0) == "1") {
                    indices.push_back(std::stoul(results.at(1)));
                }

                remainingIndices--;
            }
            else {
                std::cout << "error on line " << lineNumber << ": expecting vertex or index" << std::endl;
            }
        }
    }

    std::vector<sf::Vector2f> projection;

    for(auto const& v: vertices) {
        projection.push_back(sf::Vector2f(v.x / (1 - v.z), v.y / (1 - v.z)));
    }

    IDelaBella* idb = IDelaBella::Create();

    // int verts = idb->Triangulate(points, &vertices[0].x, &vertices[0].y, sizeof(sf::Vector2f));
    int verts = idb->Triangulate(projection.size(), &projection[0].x, &projection[0].y, sizeof(sf::Vector2f));

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
}

std::vector<sf::Vector3f> PlyLoader::GetVertices() {
    return vertices;
}

std::vector<unsigned int> PlyLoader::GetIndices() {
    return indices;
}
