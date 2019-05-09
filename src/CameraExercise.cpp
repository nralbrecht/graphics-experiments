#include <cmath>
#include <random>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "SfmlHelper.h"
#include "CameraExercise.h"
#include "CubeShape.h"
#include "SphereShape.h"
#include "MeshShape.h"

#include "PlyLoader.h"
#include "ObjLoader.h"

CameraExercise::CameraExercise(const sf::RenderWindow &window)
    : window(window)
{
}

CameraExercise::~CameraExercise() {
    for (int i = 0; i < shapes.size(); ++i) {
        delete shapes[i];
    }
}

void CameraExercise::Init() {
    eye = glm::vec3(10, 0, 0);
    la = glm::vec3(0, 0, 0);
    up = glm::vec3(0, 1, 0);
    angleX = M_PI / 4.0f;
    angleY = M_PI / 3.0f;
    radius = 10.0f;
    isMouseDown = false;
    zoom = 40.0f;

    shapes.push_back(new CubeShape(sf::Vector3f(0.0f, 0.0f, 0.0f)));
    shapes.push_back(new SphereShape(500, sf::Vector3f(0.0f, 0.0f, 0.0f), 0.5f));
    shapes.push_back(new MeshShape(new PlyLoader("./resources/bun_zipper.ply")));
    shapes.push_back(new MeshShape(new ObjLoader("./resources/cube.obj")));
    isInitialized = true;
}

bool CameraExercise::IsInitialized() {
    return isInitialized;
}

const char* CameraExercise::GetName() {
    return "Camera";
}

void CameraExercise::ProcessEvent(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            angleX -= 0.1f;
        }
        else if (event.key.code == sf::Keyboard::Right) {
            angleX += 0.1f;
        }
        else if (event.key.code == sf::Keyboard::Down && angleY > 0.1f) {
            angleY -= 0.1f;
        }
        else if (event.key.code == sf::Keyboard::Up && angleY < M_PI - 0.1f) {
            angleY += 0.1f;
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            isMouseDown = true;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            isMouseDown = false;
        }
    }
    else if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f lastMousePosition = mousePosition;
        mousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);

        if (isMouseDown) {
            mouseDelta.x += mousePosition.x - lastMousePosition.x;
            mouseDelta.y -= mousePosition.y - lastMousePosition.y;
        }
    }
    else if (event.type == sf::Event::MouseWheelScrolled) {
        zoom -= event.mouseWheelScroll.delta;

        if (zoom < 0.1f) {
            zoom = 0.1f;
        }
    }
}

void CameraExercise::Update(float timeDelta) {
    float deltaX = angleX + mouseDelta.x * 0.01f;
    float deltaY = angleY + mouseDelta.y * 0.01f;

    if (deltaY < 0.05f) {
        deltaY = 0.05f;
    }
    if (deltaY > M_PI - 0.05f) {
        deltaY = M_PI - 0.05f;
    }

    sf::Vector3f unnormalizedEye(
        radius * cos(deltaX) * sin(deltaY),
        radius * cos(deltaY),
        radius * sin(deltaX) * sin(deltaY));

    sf::Vector3f temp = normalizeToLength(unnormalizedEye, (0.0001591*zoom*zoom*zoom) - (0.002788*zoom*zoom) + (0.03712*zoom) + 0.1);
    eye.x = temp.x;
    eye.y = temp.y;
    eye.z = temp.z;
}

void CameraExercise::UpdateModelView() {
    glMatrixMode(GL_MODELVIEW);
    glm::mat4 mview = glm::lookAt(eye, la, up);
    glLoadMatrixf(&(mview[0][0]));
}

void CameraExercise::UpdateProjection() {
    sf::Vector2<unsigned int> size = window.getSize();
    float aspect = size.x / (float)size.y;
    
    float near_plane = 0.1f;
    float far_plane = 1000.f;
    float fov = glm::radians(40.0f);
    glm::mat4 projMatr = glm::perspective(fov, aspect, near_plane, far_plane);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(&(projMatr[0][0]));
}

void CameraExercise::Draw() {
    UpdateModelView();

    shapes.at(selectedObject)->Draw();
}

void CameraExercise::DrawGUI(const char* name) {
    ImGui::Begin(name);
        ImGui::ListBox("Object", &selectedObject, objects, shapes.size());
    ImGui::End();
}
