#include <random>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "SfmlHelper.h"
#include "TransformationExcercise.h"

TransformationExcercise::TransformationExcercise(const sf::RenderWindow &window)
	: window(window)
{
	angle = 0;
	touchIsActive = false;

	position = sf::Vector2f(0.0f, 0.0f);
	nextPosition = sf::Vector2f(0.5f, 0.5f);
}

void TransformationExcercise::ProcessEvent(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		// nextPosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
	}
}

void TransformationExcercise::Update(float timeDelta) {
	angle += ((float)std::rand() / (float)RAND_MAX) * 5;

	if (vectorLength(nextPosition - position) < 0.15) {
		nextPosition.x = ((((float)std::rand() / (float)RAND_MAX) * 2) - 1) * 2;
		nextPosition.y = ((((float)std::rand() / (float)RAND_MAX) * 2) - 1) * 2;
	}

	position = moveTowards(position, nextPosition, 0.1);
}

void TransformationExcercise::UpdateModelView() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(position.x, position.y, 0);
	glRotatef(angle, 0, 0, 1);
}

void TransformationExcercise::UpdateProjection() {
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    sf::Vector2<unsigned int> size = window.getSize();
    float ar = size.x / (float)size.y;
    glOrtho( -2 * ar, 2 * ar, -2, 2, -1, 1);
}

void TransformationExcercise::Draw() {
	UpdateModelView();

	glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5f,  0.5f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f,  0.5f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f,  0.5f, 0.0f);
	glEnd();
}

void TransformationExcercise::DrawGUI(const char* name) {
	ImGui::Begin(name);
		ImGui::Text("Text");
	ImGui::End();
}
