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
                if (results.at(1) == "face") {
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

                for (int i = 1; i <= std::stoi(results.at(0)); ++i) {
                    indices.push_back(std::stoul(results.at(i)));
                }

                remainingIndices--;
            }
            else {
                std::cout << "error on line " << lineNumber << ": expecting vertex or index" << std::endl;
                throw;
            }
        }
    }
}

std::vector<sf::Vector3f> PlyLoader::GetVertices() {
    return vertices;
}

std::vector<unsigned int> PlyLoader::GetIndices() {
    return indices;
}
