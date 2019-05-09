#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

#include <SFML/System/Vector3.hpp>

#include "ObjLoader.h"
#include "SfmlHelper.h"

ObjLoader::ObjLoader(const char* path) {
    std::ifstream is(path);
    
    int lineNumber = 0;

    std::string line;
    while(std::getline(is, line)) {
        lineNumber++;
        std::vector<std::string> tokkens = split(line, ' ');

        if (tokkens.at(0) == "v") {
            vertices.push_back(sf::Vector3f(std::stof(tokkens.at(1)), std::stof(tokkens.at(2)), std::stof(tokkens.at(3))));
        }
        else if (tokkens.at(0) == "vn") {
            normals.push_back(sf::Vector3f(std::stof(tokkens.at(1)), std::stof(tokkens.at(2)), std::stof(tokkens.at(3))));
        }
        else if (tokkens.at(0) == "f") {

            for (int i = 1; i < tokkens.size(); ++i) {
                std::vector<std::string> index = split(tokkens.at(i), '/');

                if (index.size() == 1) {
                    // f 1 2 3

                    indices.push_back((unsigned int)std::stoul(index.at(0)));
                }
                else if (index.size() == 3) {
                    // f 2//1 3//1 4//1
                    // f 2/3/1 3/4/1 4/6/1

                    indices.push_back((unsigned int)std::stoul(index.at(0)) - 1);
                    normalIndices.push_back((unsigned int)std::stoul(index.at(2)) - 1);
                }
            }
        }
    }
}

std::vector<sf::Vector3f> ObjLoader::GetNormals() {
    return normals;
}

std::vector<sf::Vector3f> ObjLoader::GetVertices() {
    return vertices;
}

std::vector<unsigned int> ObjLoader::GetIndices() {
    return indices;
}

std::vector<unsigned int> ObjLoader::GetNormalIndices() {
    return normalIndices;
}
