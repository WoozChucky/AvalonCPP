//
// Created by Nuno Levezinho on 07/02/2018.
//

#ifndef AVALONENGINE_STATE_H
#define AVALONENGINE_STATE_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "../../UI/Engine/Events/EventType.h"
#include "../../EventBus/Subject.h"

namespace av
{
    class State
    {
    public:
        virtual ~State() = default;
        explicit State(const sf::Vector2f l_window_size);

        virtual void Update(float timestep) = 0;
        virtual void Render(sf::RenderWindow& l_window) = 0;
        virtual void HandleInput(sf::Event& l_event) = 0;

        sf::Vector2f GetWindowSize() const;
        void SetWindowSize(const sf::Vector2f l_window_size);

        Subject<EventType::State>* GetStateManager() const;
        void SetStateManager(Subject<EventType::State>* l_subject);

    private:
        sf::Vector2f m_window_size_;
        Subject<EventType::State> * m_state_manager_;
    };
}


#endif //AVALONENGINE_STATE_H
