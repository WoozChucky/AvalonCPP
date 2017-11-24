#include "GameState.hpp"

av::state::GameState::GameState() : m_player_()
{
	for (auto i = 0; i < 5; i++)
	{
		entities::Enemy temp(sf::Vector2f(50.f, 50.f), entities::Class::Warrior);
		m_enemies_.push_back(temp);
	}
}

void av::state::GameState::Update(const float timestep)
{
	// Update player status
	this->m_player_.Update(timestep);

	// Check if any bullet collides with enemies, then erase them from screen
	for(auto i = 0; i < this->m_player_.m_bullets.size(); i++)
	{
		for(auto j = 0; j < this->m_enemies_.size(); j++)
		{
			if(this->m_enemies_[j].Collide(this->m_player_.m_bullets[i]))
			{   //Bullet collided with Enemy
				//Erase bullet
				this->m_player_.m_bullets.erase(this->m_player_.m_bullets.begin() + i);
				if(!this->m_enemies_[j].IsAlive())
				{	//Enemy died, erase it
					this->m_enemies_.erase(this->m_enemies_.begin() + j);
					//TODO: Add points to scoreboard
					//NOTE: Maybe enemies can drop 'powerups' on death ?
				}
			}
		}
		this->m_enemies_.at(i).Update(timestep);
	}
	
	//Spawn Enemy if we have less than 5 on screen.
	if(this->m_enemies_.size() < 5)
	{
		for(auto i = 0; i < 5 - this->m_enemies_.size(); i++)
		{
			entities::Enemy temp(sf::Vector2f(50.f, 50.f), entities::Class::Warrior);
			this->m_enemies_.push_back(temp);
		}
	}
}

void av::state::GameState::Render(sf::RenderWindow& l_window)
{
	this->m_player_.Render(l_window);
	for (auto i = 0; i < this->m_enemies_.size(); i++)
	{
		this->m_enemies_.at(i).Render(l_window);
	}
}

void av::state::GameState::HandleInput(const sf::Event l_event)
{
	this->m_player_.HandleInput(l_event);

	if(l_event.type == sf::Event::LostFocus) 
	{
		this->m_requires_pause = true;
	}

	if(l_event.type == sf::Event::EventType::KeyPressed)
	{
		if(l_event.key.code == sf::Keyboard::Key::Escape) {
			this->m_requires_pause = true;
		}
	}

}

void av::state::GameState::Restart()
{
	this->m_enemies_.clear();
	for (auto i = 0; i < 5; i++)
	{
		entities::Enemy temp(sf::Vector2f(50.f, 50.f), entities::Class::Warrior);
		m_enemies_.push_back(temp);
	}
	this->m_player_.Restart();
}