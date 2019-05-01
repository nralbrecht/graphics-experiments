#ifndef TRANSFORMATION_EXCERCISE_H
#define TRANSFORMATION_EXCERCISE_H

#include <SFML/Graphics.hpp>

#include "IExcercise.h"

class TransformationExcercise : public IExcercise
{
private:
	const sf::RenderWindow &window;
	float angle;
	bool touchIsActive;
	sf::Vector2f position;
	sf::Vector2f nextPosition;

public:
	TransformationExcercise(const sf::RenderWindow &window);
	const char* GetName();
    void ProcessEvent(sf::Event event);
    void Update(float timeDelta);
    void UpdateModelView();
    void UpdateProjection();
    void Draw();
    void DrawGUI(const char* name);
};

#endif
