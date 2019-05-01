#include <cmath>
#include <vector>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "SfmlHelper.h"
#include "BezierExcercise.h"

sf::Vector2f BezierExcercise::B(std::vector<sf::Vector2f> coorArr, int i, int j, float at) {
    if (j == 0) {
        return coorArr[i];
    }
    else {
        sf::Vector2f a = B(coorArr, i, j - 1, at);
        a.x *= (1 - at);
        a.y *= (1 - at);
        
        sf::Vector2f b = B(coorArr, i + 1, j - 1, at);
        b.x *= at;
        b.y *= at;

        return a + b;
    }
}

std::vector<sf::Vector2f> BezierExcercise::getPolylineBesier(std::vector<sf::Vector2f> controllPoints, int stepCount) {
    std::vector<sf::Vector2f> result;
    for (int i = 0; i < stepCount; ++i) {
        float t = float(i) / (stepCount - 1);
        result.push_back(B(controllPoints, 0, controllPoints.size() - 1, t));
    }

    return result;
}

BezierExcercise::BezierExcercise(const sf::RenderWindow &window)
	: window(window)
{	
	color = 0.0f;
	stepCount = 30;
	lineWidth = 0.2;
	simulationSpeed = 1.0f;

	drawSteps = false;
	drawModifiers = true;
	drawCenterline = false;
	drawModifierLine = true;

	stepColor = sf::Vector3f(1.0f, 0.0f, 0.0f);
	centerlineColor = sf::Vector3f(0.0f, 0.0f, 0.0f);
	modifierLineColor = sf::Vector3f(0.1f, 0.1f, 1.0f);
	modifierColor = sf::Vector3f(0.0f, 0.0f, 1.0f);
	lineColor = sf::Vector3f(0.0f, 0.0f, 0.0f);

    modifier.push_back(sf::Vector2f(-1.0f, 0.0f));
    modifier.push_back(sf::Vector2f(-1.0f, -1.0f));
    modifierTarget.push_back(sf::Vector2f(-1.0f, -1.0f));
    modifier.push_back(sf::Vector2f(0.0f, -1.0f));
    // modifierTarget.push_back(sf::Vector2f(0.0f, -1.0f));
    // modifier.push_back(sf::Vector2f(0.0f, 1.0f));
    // modifierTarget.push_back(sf::Vector2f(0.0f, 1.0f));
    // modifier.push_back(sf::Vector2f(1.0f, 1.0f));
    modifierTarget.push_back(sf::Vector2f(1.0f, 1.0f));
    modifier.push_back(sf::Vector2f(1.0f, 0.0f));
}

void BezierExcercise::ProcessEvent(sf::Event event) {}

void BezierExcercise::Update(float timeDelta) {
	// Move Points
	for (int i = 1; i < modifier.size() - 1; ++i) {
	    if (vectorLength(modifierTarget[i - 1] - modifier[i]) < 0.15) {
	        modifierTarget[i - 1].x = ((((float)std::rand() / (float)RAND_MAX) * 2) - 1) * 2;
	        modifierTarget[i - 1].y = ((((float)std::rand() / (float)RAND_MAX) * 2) - 1) * 2;
	    }

	    modifier[i] = moveTowards(modifier[i], modifierTarget[i - 1], 0.1 * simulationSpeed);
	}

	// Approximate Points
    steps = getPolylineBesier(modifier, stepCount);

    // Color
    color += 0.001f * simulationSpeed;
    if (color > 1) {
        color = 0.0f;
    }

    lineColor = getColor(color);
}

void BezierExcercise::UpdateModelView() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void BezierExcercise::UpdateProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    sf::Vector2<unsigned int> size = window.getSize();
    float ar = size.x / (float)size.y;
    glOrtho( -2 * ar, 2 * ar, -2, 2, -1, 1);
}

void BezierExcercise::Draw() {
    for (int i = 0; i < steps.size() - 1; ++i) {
        sf::Vector3f tempCross = crossProduct(sf::Vector3f(steps[i].x, steps[i].y, 0.0f) - sf::Vector3f(steps[i + 1].x, steps[i + 1].y, 0.0f), sf::Vector3f(0.0f,0.0f,-1.0f));
        sf::Vector2f cross = normalizeToLength(sf::Vector2f(tempCross.x, tempCross.y), lineWidth);
        
        if (i < steps.size() - 2) {
            tempCross = crossProduct(sf::Vector3f(steps[i + 1].x, steps[i + 1].y, 0.0f) - sf::Vector3f(steps[i + 2].x, steps[i + 2].y, 0.0f), sf::Vector3f(0.0f,0.0f,-1.0f));
            sf::Vector2f crossNext = normalizeToLength(sf::Vector2f(tempCross.x, tempCross.y), lineWidth);
            
            drawTriangle(steps[i + 1], steps[i + 1] - cross, steps[i + 1] - crossNext, lineColor);
            drawTriangle(steps[i + 1], steps[i + 1] + cross, steps[i + 1] + crossNext, lineColor);
        }
        
        drawTriangle(steps[i] + cross, steps[i] - cross, steps[i + 1] - cross, lineColor);
        drawTriangle(steps[i + 1] - cross, steps[i + 1] + cross, steps[i] + cross, lineColor);

        if (drawCenterline) {
            drawLine(steps[i], steps[i + 1], centerlineColor);
        }
    }

    if (drawSteps) {
        glColor3f(1.0f, 0.0f, 0.0f);
        for (int i = 0; i < steps.size(); ++i) {
            drawPoint(steps[i], stepColor);
        }
    }


    if (drawModifiers) {
        drawCircle(modifier[0], lineWidth, 8, lineColor);
        for (int i = 1; i < modifier.size() - 1; ++i) {
            drawCircle(modifier[i], 0.03, 8, modifierColor);
        }
        drawCircle(modifier[modifier.size() - 1], lineWidth, 8, lineColor);
    }

    if (drawModifierLine) {
        for (int i = 0; i < modifier.size() - 1; ++i) {
            drawLine(modifier[i], modifier[i + 1], modifierLineColor);
        }
    }
}

void BezierExcercise::DrawGUI(const char* name) {
	ImGui::Begin(name);
        ImGui::Checkbox("Steps", &drawSteps);
        ImGui::Checkbox("Modifier", &drawModifiers);
        ImGui::Checkbox("Centerline", &drawCenterline);
        ImGui::Checkbox("Modifier Line", &drawModifierLine);
        ImGui::Separator();
        ImGui::DragFloat("Speed", &simulationSpeed, 0.005f, 0.0f, 3.0f);
        ImGui::DragFloat("Line Width", &lineWidth, 0.01f, 0.0f, 1.5f);
        ImGui::DragInt("Step Count", &stepCount, 1, 2, 100);
        ImGui::Separator();

        int flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_InputRGB;
        ImGui::ColorEdit3("Line Color", &lineColor.x, flags);
        ImGui::ColorEdit3("Step Color", &stepColor.x, flags);
        ImGui::ColorEdit3("Modifier Color", &modifierColor.x, flags);
        ImGui::ColorEdit3("Modifier Line Color", &modifierLineColor.x, flags);
        ImGui::ColorEdit3("Centerline Color", &centerlineColor.x, flags);
    ImGui::End();
}
