#pragma once

#include <vector>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "IExercise.h"

class BezierExercise : public IExercise
{
private:
    bool isInitialized;
    const sf::RenderWindow &window;

    float color;
    int stepCount;
    float lineWidth;
    float simulationSpeed;

    bool drawSteps;
    bool drawModifiers;
    bool drawCenterline;
    bool drawModifierLine;

    sf::Vector3f lineColor;
    sf::Vector3f stepColor;
    sf::Vector3f modifierColor;
    sf::Vector3f modifierLineColor;
    sf::Vector3f centerlineColor;

    std::vector<sf::Vector2f> steps;
    std::vector<sf::Vector2f> modifier;
    std::vector<sf::Vector2f> modifierTarget;

    sf::Vector2f B(std::vector<sf::Vector2f> coorArr, int i, int j, float at);
    std::vector<sf::Vector2f> getPolylineBesier(std::vector<sf::Vector2f> controllPoints, int stepCount);

public:
    BezierExercise(const sf::RenderWindow &window);
    void Init();
    bool IsInitialized();
    const char* GetName();
    void ProcessEvent(sf::Event event);
    void Update(float timeDelta);
    void UpdateModelView();
    void UpdateProjection();
    void Draw();
    void DrawGUI(const char* name);
};
