#include "State.h"

using namespace av;

State::State(const sf::Vector2f l_window_size)
	: m_StateManager(nullptr)
{
	this->m_WindowSize = l_window_size;
}

sf::Vector2f State::GetWindowSize() const
{
	return this->m_WindowSize;
}

Subject<EventType::State>* State::GetStateManager() const
{
	return this->m_StateManager;
}

void State::SetStateManager(Subject<EventType::State>* l_subject)
{
	this->m_StateManager = l_subject;
}