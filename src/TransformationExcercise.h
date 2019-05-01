#ifndef TRANSFORMATION_EXCERCISE_H
#define TRANSFORMATION_EXCERCISE_H

#include "IExcercise.h"
#include <SFML/Graphics.hpp>

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
    void ProcessEvent(sf::Event event);
    void Update(float timeDelta);
    void UpdateModelView();
    void UpdateProjection();
    void Draw();
    void DrawGUI(const char* name);
};

#endif
