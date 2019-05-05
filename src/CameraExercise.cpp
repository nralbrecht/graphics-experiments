#include <random>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "SfmlHelper.h"
#include "CameraExercise.h"

CameraExercise::CameraExercise(const sf::RenderWindow &window)
	: window(window)
{
}

void CameraExercise::Init() {
	eye = glm::vec3(0, 0, 10);
	la = glm::vec3(0, 0, 0);
	up = glm::vec3(0, 1, 0);
	angleX = 0.0f;
	angleY = 0.0f;
	radius = 10.0f;
	
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
			angleX += 0.1f;
		}
		else if (event.key.code == sf::Keyboard::Right) {
			angleX -= 0.1f;
		}
		else if (event.key.code == sf::Keyboard::Down) {
			angleY += 0.1f;
		}
		else if (event.key.code == sf::Keyboard::Up) {
			angleY -= 0.1f;
		}
	}
}

void CameraExercise::Update(float timeDelta) {
	eye.x = radius * cos(angleX) * sin(angleY);
	eye.y = radius * sin(angleX) * sin(angleY);
	eye.z = radius * cos(angleY);
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

	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// glOrtho( -2 * aspect, 2 * aspect, -2, 2, -2, 2);
}

void CameraExercise::Draw() {
	UpdateModelView();

	glBegin(GL_TRIANGLES);

	glColor3f(1.0f,  1.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	glColor3f(1.0f,  0.0f,  1.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glColor3f(0.0f,  1.0f,  0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glColor3f(0.0f,  0.0f,  1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	glColor3f(1.0f,  0.0f,  0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	glColor3f(0.0f,  0.0f,  0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glEnd();
}

void CameraExercise::DrawGUI(const char* name) {
	ImGui::Begin(name);
		ImGui::Text("Text");
	ImGui::End();
}
