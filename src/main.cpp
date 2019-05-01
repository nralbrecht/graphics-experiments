#include <vector>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "IExcercise.h"
#include "BezierExcercise.h"
#include "CameraExcercise.h"
#include "TransformationExcercise.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Kurven", sf::Style::Default, sf::ContextSettings(24, 8, 4, 1, 1));
	// sf::Window window(sf::VideoMode(800, 600), "OpenGL Tutorial 03", sf::Style::Default, sf::ContextSettings(24, 8, 4, 3, 2));
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);

	window.resetGLStates();
	sf::Clock deltaClock;

	int currentExercise = 2;
	
	std::vector<IExcercise*> exercises;
	exercises.push_back(new TransformationExcercise(window));
	exercises.push_back(new BezierExcercise(window));
	exercises.push_back(new CameraExcercise(window));
	
	exercises[currentExercise]->UpdateProjection();

	bool running = true;
	while (running)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			exercises[currentExercise]->ProcessEvent(event);

			if (event.type == sf::Event::Closed)
			{
				running = false;
				std::printf("closing...\n");
			}
			else if (event.type == sf::Event::Resized)
			{
				glViewport(0, 0, event.size.width, event.size.height);

				exercises[currentExercise]->UpdateProjection();

				std::printf("resized x:%d, y:%d\n", event.size.width, event.size.height);
			}
		}

		sf::Time deltaTime = deltaClock.restart();
		ImGui::SFML::Update(window, deltaTime);
		
		ImGui::SetNextWindowPos(sf::Vector2f(0.0f, 0.0f));
		ImGui::SetNextWindowSize(sf::Vector2f(window.getSize().x, -1.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
		ImGui::Begin("Tab Test", NULL, ImGuiWindowFlags_NoDecoration  | ImGuiWindowFlags_NoMove);
		if (ImGui::BeginTabBar("id")){
			if (ImGui::BeginTabItem("Transformationen")) {
				window.setTitle("Transformationen");

				if (currentExercise != 0) {
					currentExercise = 0;
					exercises[currentExercise]->UpdateProjection();
					exercises[currentExercise]->UpdateModelView();
				}

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Kurven")) {
				window.setTitle("Kurven");
				if (currentExercise != 1) {
					currentExercise = 1;
					exercises[currentExercise]->UpdateProjection();
					exercises[currentExercise]->UpdateModelView();
				}

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Kamera")) {
				window.setTitle("Kamera");
				if (currentExercise != 2) {
					currentExercise = 2;
					exercises[currentExercise]->UpdateProjection();
					exercises[currentExercise]->UpdateModelView();
				}

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();
		ImGui::PopStyleVar();

		exercises[currentExercise]->Update(deltaTime.asSeconds());

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.1f,0.1f,0.1f,0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		exercises[currentExercise]->Draw();
		
		window.pushGLStates();
		exercises[currentExercise]->DrawGUI("Config");
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