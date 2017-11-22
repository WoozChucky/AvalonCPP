#include "GameState.hpp"

av::state::GameState::GameState() : m_player_(),
temp(sf::Vector2f(200.f, 50.f), sf::Vector2f(300.f, 250.f), "OK")
{
	for (auto i = 0; i < 5; i++)
	{
		entities::Enemy temp(sf::Vector2f(50.f, 50.f), entities::Class::Warrior);
		m_enemies_.push_back(temp);
	}
}

av::state::GameState::~GameState()
{
}

void av::state::GameState::Update(const float timestep)
{
	for(auto i = 0; i < this->m_enemies_.size(); i++)
	{
		this->m_enemies_.at(0).Update(timestep);
	}
	
}

void av::state::GameState::Render(sf::RenderWindow& l_window)
{
	for (auto i = 0; i < this->m_enemies_.size(); i++)
	{
		this->m_enemies_.at(0).Render(l_window);
	}

	temp.Render(l_window);
}

void av::state::GameState::HandleInput()
{

}

void av::state::GameState::Restart()
{
	
}