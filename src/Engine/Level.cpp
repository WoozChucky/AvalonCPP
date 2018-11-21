#include "Level.h"

using namespace av;

Level::Level(const sf::Vector2f l_bounds)
	: m_Bounds(l_bounds), m_LevelManager(nullptr)
{
}

Subject<EventType::Level>* Level::GetLevelManager() const
{
	return this->m_LevelManager;
}

void Level::SetLevelManager(Subject<EventType::Level>* l_subject)
{
	this->m_LevelManager = l_subject;
}

sf::Vector2f Level::GetBounds() const
{
	return this->m_Bounds;
}


