#include <vector>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "IExercise.h"
#include "BezierExercise.h"
#include "CameraExercise.h"
#include "DelaunayExercise.h"
#include "TransformationExercise.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graphics Experiments", sf::Style::Default, sf::ContextSettings(24, 8, 4, 1, 1));
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    window.resetGLStates();
    sf::Clock deltaClock;

    int currentExercise = 2;
    
    std::vector<IExercise*> exercises;
    exercises.push_back(new TransformationExercise(window));
    exercises.push_back(new BezierExercise(window));
    exercises.push_back(new CameraExercise(window));
    exercises.push_back(new DelaunayExercise(window));
    
    exercises.at(currentExercise)->Init();
    exercises.at(currentExercise)->UpdateProjection();

    bool running = true;
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            exercises.at(currentExercise)->ProcessEvent(event);

            if (event.type == sf::Event::Closed)
            {
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                glViewport(0, 0, event.size.width, event.size.height);

                exercises.at(currentExercise)->UpdateProjection();
            }
        }

        sf::Time deltaTime = deltaClock.restart();
        ImGui::SFML::Update(window, deltaTime);
        
        ImGui::SetNextWindowPos(sf::Vector2f(0.0f, 0.0f));
        ImGui::SetNextWindowSize(sf::Vector2f(window.getSize().x, -1.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
        ImGui::Begin("Tab Test", NULL, ImGuiWindowFlags_NoDecoration  | ImGuiWindowFlags_NoMove);
        if (ImGui::BeginTabBar("id")){
            for (int i = 0; i < exercises.size(); ++i) {
                if (ImGui::BeginTabItem(exercises.at(i)->GetName())) {
                    window.setTitle(exercises.at(i)->GetName());

                    if (currentExercise != i) {
                        currentExercise = i;
                        
                        if (!exercises.at(currentExercise)->IsInitialized()) {
                            exercises.at(currentExercise)->Init();
                        }

                        exercises.at(currentExercise)->UpdateProjection();
                        exercises.at(currentExercise)->UpdateModelView();
                    }

                    ImGui::EndTabItem();
                }
            }

            ImGui::EndTabBar();
        }
        ImGui::End();
        ImGui::PopStyleVar();

        exercises.at(currentExercise)->Update(deltaTime.asSeconds());

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f,0.1f,0.1f,0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        exercises.at(currentExercise)->Draw();
        
        window.pushGLStates();
        exercises.at(currentExercise)->DrawGUI("Config");
        ImGui::SFML::Render(window);
        window.popGLStates();

        window.display();
    }

    for (int i = 0; i < exercises.size(); ++i) {
        delete exercises[i];
    }

    ImGui::SFML::Shutdown();

    return 0;
}
