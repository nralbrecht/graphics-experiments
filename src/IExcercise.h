#ifndef I_EXCERCISE_H
#define I_EXCERCISE_H

#include <SFML/Window/Event.hpp>

class IExcercise
{
    public:
        virtual ~IExcercise() {}
        virtual void ProcessEvent(sf::Event event) = 0;
        virtual void Update(float timeDelta) = 0;
        virtual void UpdateModelView() = 0;
        virtual void UpdateProjection() = 0;
        virtual void Draw() = 0;
        virtual void DrawGUI(const char* name) = 0;
};

#endif
