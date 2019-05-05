#pragma once

#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "IExercise.h"

class DelaunayExercise : public IExercise
{
private:
	const sf::RenderWindow &window;

	int pointCount;
	bool wireframe;
	bool drawPoints;
	std::vector<int> indices;
	std::vector<sf::Vector2f> points;

public:
	DelaunayExercise(const sf::RenderWindow &window);
	const char* GetName();
    void ProcessEvent(sf::Event event);
    void Update(float timeDelta);
    void UpdateModelView();
    void UpdateProjection();
    void Draw();
    void DrawGUI(const char* name);

    void UpdatePoints();
};
