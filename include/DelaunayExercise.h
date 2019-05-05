#pragma once

#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "IExercise.h"

class DelaunayExercise : public IExercise
{
private:
    bool isInitialized;
    const sf::RenderWindow &window;

    int pointCount;
    bool drawPoints;
    bool fillTriangles;
    float simulationSpeed;
    sf::Vector3f fillColor;
    sf::Vector3f lineColor;
    std::vector<int> indices;
    std::vector<sf::Vector2f> points;
    std::vector<sf::Vector2f> targets;

public:
    DelaunayExercise(const sf::RenderWindow &window);
    void Init();
    bool IsInitialized();
    const char* GetName();
    void ProcessEvent(sf::Event event);
    void Update(float timeDelta);
    void UpdateModelView();
    void UpdateProjection();
    void Draw();
    void DrawGUI(const char* name);

    void Triangulate();
    void UpdatePoints();
};
