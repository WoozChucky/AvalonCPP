//
// Created by Nuno Levezinho on 07/02/2018.
//

#include "State.h"

av::State::State(const sf::Vector2f l_window_size)
{
    this->m_window_size_ = l_window_size;
}

sf::Vector2f av::State::GetWindowSize() const
{
    return this->m_window_size_;
}

av::Subject<av::EventType::State>* av::State::GetStateManager() const
{
    return this->m_state_manager_;
}

void av::State::SetStateManager(Subject<EventType::State>* l_subject)
{
    this->m_state_manager_ = l_subject;
}
