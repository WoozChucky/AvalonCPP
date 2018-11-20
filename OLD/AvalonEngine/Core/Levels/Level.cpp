//
// Created by Nuno Levezinho on 07/02/2018.
//

#include "Level.h"

av::Level::Level(sf::Vector2f l_bounds)
{
    this->m_bounds_ = l_bounds;
}

av::Subject<av::EventType::Level>* av::Level::GetLevelManager() const
{
    return this->m_level_manager_;
}

void av::Level::SetLevelManager(Subject<EventType::Level>* l_subject)
{
    this->m_level_manager_ = l_subject;
}

sf::Vector2f av::Level::GetBounds()
{
    return this->m_bounds_;
}