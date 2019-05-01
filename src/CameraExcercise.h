#ifndef CAMERA_EXCERCISE_H
#define CAMERA_EXCERCISE_H

#include "IExcercise.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <glm/vec3.hpp>

class CameraExcercise : public IExcercise
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
	CameraExcercise(const sf::RenderWindow &window);
    void ProcessEvent(sf::Event event);
    void Update(float timeDelta);
    void UpdateModelView();
    void UpdateProjection();
    void Draw();
    void DrawGUI(const char* name);
};

#endif
