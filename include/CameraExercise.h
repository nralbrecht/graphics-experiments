#pragma once

#include <glm/vec3.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "IExercise.h"
#include "IShape.h"

class CameraExercise : public IExercise
{
private:
    bool isInitialized;
    const sf::RenderWindow &window;
    glm::vec3 eye;
    glm::vec3 la;
    glm::vec3 up;
    float angleX;
    float angleY;
    float radius;

    int selectedObject = 0;
    const char* objects[3] = { "Cube", "Sphere", "Bunny" };
    std::vector<IShape*> shapes;

    float zoom;
    bool isMouseDown;
    sf::Vector2f mouseDelta;
    sf::Vector2f mousePosition;

public:
    CameraExercise(const sf::RenderWindow &window);
    ~CameraExercise();
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
