#include <random>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <delabella.h>

#include "SfmlHelper.h"
#include "DelaunayExercise.h"

DelaunayExercise::DelaunayExercise(const sf::RenderWindow &window)
	: window(window)
{
}

void DelaunayExercise::Init() {
	pointCount = 10;
	wireframe = true;
	drawPoints = true;
	this->UpdatePoints();

	isInitialized = true;
}

bool DelaunayExercise::IsInitialized() {
    return isInitialized;
}

const char* DelaunayExercise::GetName() {
    return "Delaunay Triangulation";
}

void DelaunayExercise::ProcessEvent(sf::Event event) {}

void DelaunayExercise::Update(float timeDelta) {
}

void DelaunayExercise::UpdateModelView() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void DelaunayExercise::UpdateProjection() {
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    sf::Vector2<unsigned int> size = window.getSize();
    float ar = size.x / (float)size.y;
    glOrtho( -2 * ar, 2 * ar, -2, 2, -1, 1);
}

void DelaunayExercise::Draw() {
	UpdateModelView();

	if (wireframe) {
		glBegin(GL_LINES);
			glColor3f(0.0f, 1.0f, 0.0f);
			for (int i = 0; i < indices.size() - 2; i += 3) {
				const sf::Vector2f v1 = points.at(indices.at(i));
				const sf::Vector2f v2 = points.at(indices.at(i + 1));
				const sf::Vector2f v3 = points.at(indices.at(i + 2));

				glVertex2f(v1.x, v1.y);
				glVertex2f(v2.x, v2.y);

				glVertex2f(v2.x, v2.y);
				glVertex2f(v3.x, v3.y);
				
				glVertex2f(v3.x, v3.y);
				glVertex2f(v1.x, v1.y);
			}
		glEnd();
	}
	else {
		glBegin(GL_TRIANGLES);
			glColor3f(0.0f, 1.0f, 0.0f);
			for(auto const& index: indices) {
				const sf::Vector2f v = points.at(index);
				glVertex2f(v.x, v.y);
			}
		glEnd();
	}

	if (drawPoints) {
		for(auto const& point: points) {
			drawCircle(point, 0.02f, 20, sf::Vector3f(1.1f, 1.0f, 0.1f));
		}
	}
}

void DelaunayExercise::DrawGUI(const char* name) {
	ImGui::Begin(name);
		ImGui::Checkbox("Wireframe", &wireframe);
		ImGui::Checkbox("Draw Points", &drawPoints);
		if (ImGui::Button("Randomise")) {
			this->UpdatePoints();
		}
	ImGui::End();
}

void DelaunayExercise::UpdatePoints() {
	points.clear();
	indices.clear();

	for (int i = 0; i < pointCount; i++) {
		points.push_back(sf::Vector2f(((float) rand() / (RAND_MAX)), ((float) rand() / (RAND_MAX))));
	}

	IDelaBella* idb = IDelaBella::Create();

	int verts = idb->Triangulate(pointCount, &points[0].x, &points[0].y, sizeof(sf::Vector2f));

	if (verts > 0) {
		int tris = verts / 3;
		const DelaBella_Triangle* dela = idb->GetFirstDelaunayTriangle();
		for (int i = 0; i < tris; i++) {
			indices.push_back(dela->v[0]->i);
			indices.push_back(dela->v[1]->i);
			indices.push_back(dela->v[2]->i);

			dela = dela->next;
		}
	}
	else {
		printf("could not triangulate: %d\n", verts);
	}

	idb->Destroy();
}
