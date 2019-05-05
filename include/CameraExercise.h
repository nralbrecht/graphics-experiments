#pragma once

#include <glm/vec3.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "IExercise.h"

class CameraExercise : public IExercise
{
private:
	const sf::RenderWindow &window;
	glm::vec3 eye;
	glm::vec3 la;
	glm::vec3 up;
	float angleX;
	float angleY;
	float radius;

public:
	CameraExercise(const sf::RenderWindow &window);
	const char* GetName();
	void ProcessEvent(sf::Event event);
	void Update(float timeDelta);
	void UpdateModelView();
	void UpdateProjection();
	void Draw();
	void DrawGUI(const char* name);
};
