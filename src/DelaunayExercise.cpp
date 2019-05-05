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
    drawPoints = true;
    fillTriangles = true;
    simulationSpeed = 0.5;

    fillColor = sf::Vector3f(0.0f, 0.5f, 0.0f);
    lineColor = sf::Vector3f(0.0f, 1.0f, 0.0f);

    this->UpdatePoints();
    this->Triangulate();

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
    for (int i = 0; i < points.size(); ++i) {
        if (vectorLength(targets.at(i) - points.at(i)) < 0.15) {
            targets.at(i).x = ((((float)std::rand() / (float)RAND_MAX) * 2) - 1) * 2;
            targets.at(i).y = ((((float)std::rand() / (float)RAND_MAX) * 2) - 1) * 2;
        }

        points[i] = moveTowards(points[i], targets.at(i), 0.1 * timeDelta * simulationSpeed * 20);
    }

    this->Triangulate();
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
    if (drawPoints) {
        for(auto const& point: points) {
            drawCircle(point, 0.02f, 20, lineColor);
        }
    }

    glBegin(GL_LINES);
        glColor3f(lineColor.x, lineColor.y, lineColor.z);
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

    if (fillTriangles) {
        glBegin(GL_TRIANGLES);
            glColor3f(fillColor.x, fillColor.y, fillColor.z);
            for(auto const& index: indices) {
                const sf::Vector2f v = points.at(index);
                glVertex2f(v.x, v.y);
            }
        glEnd();
    }
}

void DelaunayExercise::DrawGUI(const char* name) {
    ImGui::Begin(name);
        ImGui::Checkbox("Fill Triangles", &fillTriangles);
        ImGui::Checkbox("Draw Points", &drawPoints);
        ImGui::DragFloat("Speed", &simulationSpeed, 0.005f, 0.0f, 1.0f);
        if (ImGui::DragInt("Point Count", &pointCount, 0.1f, 3, 50)) {
            this->UpdatePoints();
            this->Triangulate();
        }
        if (ImGui::Button("Randomise")) {
            this->UpdatePoints();
            this->Triangulate();
        }

        int flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_InputRGB;
        ImGui::ColorEdit3("Line Color", &lineColor.x, flags);
        ImGui::ColorEdit3("Fill Color", &fillColor.x, flags);
    ImGui::End();
}

void DelaunayExercise::UpdatePoints() {
    points.clear();
    targets.clear();
    
    for (int i = 0; i < pointCount; i++) {
        points.push_back(sf::Vector2f(
            (((float) rand() / (RAND_MAX)) * 2) - 0.5, 
            (((float) rand() / (RAND_MAX)) * 2) - 0.5));
        targets.push_back(sf::Vector2f(
            (((float) rand() / (RAND_MAX)) * 2) - 0.5, 
            (((float) rand() / (RAND_MAX)) * 2) - 0.5));
    }
}

void DelaunayExercise::Triangulate() {
    indices.clear();

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
