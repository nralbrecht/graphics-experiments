#pragma once

#include <SFML/Window/Event.hpp>

class IExercise
{
    public:
        virtual ~IExercise() {}
        virtual void Init() = 0;
        virtual bool IsInitialized() = 0;
        virtual const char* GetName() = 0;
        virtual void ProcessEvent(sf::Event event) = 0;
        virtual void Update(float timeDelta) = 0;
        virtual void UpdateModelView() = 0;
        virtual void UpdateProjection() = 0;
        virtual void Draw() = 0;
        virtual void DrawGUI(const char* name) = 0;
};
