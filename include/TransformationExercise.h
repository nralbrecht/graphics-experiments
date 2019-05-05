#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "IExercise.h"

class TransformationExercise : public IExercise
{
private:
	bool isInitialized;
	const sf::RenderWindow &window;
	
	float angle;
	bool touchIsActive;
	sf::Vector2f position;
	sf::Vector2f nextPosition;

public:
	TransformationExercise(const sf::RenderWindow &window);
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
