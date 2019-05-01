#pragma once

#include <SFML/Graphics.hpp>

// Vector Helper
float vectorLength(sf::Vector2f v);
sf::Vector2f normalizeToLength(sf::Vector2f v, float length);
sf::Vector3f crossProduct(sf::Vector3f a, sf::Vector3f b);
sf::Vector2f moveTowards(sf::Vector2f from, sf::Vector2f to, float distance);

// OpenGL Draw Helper
void drawTriangle(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector3f color);
void drawCircle(sf::Vector2f center, float radius, int segments, sf::Vector3f color);
void drawLine(sf::Vector2f from, sf::Vector2f to, sf::Vector3f color);
void drawPoint(sf::Vector2f v, sf::Vector3f color);
sf::Vector3f getColor(float x);
