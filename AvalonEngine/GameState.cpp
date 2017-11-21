#include "GameState.hpp"

av::GameState::GameState() : m_Player()
{
	for (auto i = 0; i < 5; i++)
	{
		Enemy temp(sf::Vector2f(50.f, 50.f), av::Class::Warrior);
		m_Enemies.push_back(temp);
	}
}

av::GameState::~GameState()
{
}

void av::GameState::Update(float timestep)
{
	for(auto i = 0; i < this->m_Enemies.size(); i++)
	{
		this->m_Enemies.at(0).Update(timestep);
	}
	
}

void av::GameState::Render(sf::RenderWindow& l_Window)
{
	for (auto i = 0; i < this->m_Enemies.size(); i++)
	{
		this->m_Enemies.at(0).Render(l_Window);
	}
}

void av::GameState::HandleInput()
{
}
