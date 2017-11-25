#include "GameState.hpp"
#include "../Generators/EntityGenerator.hpp"

av::state::GameState::GameState() : m_player_()
{

}

void av::state::GameState::Update(const float timestep)
{
	// Update player status
	this->m_player_.Update(timestep);

	//this->HandleCollision();
	
	//Spawn Enemy if we have less than 5 on screen.
	generators::EntityGenerator::Generate(this->m_enemies_, 5);
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
#if !DEBUG
		this->m_requires_pause = true;
#endif
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
	
	generators::EntityGenerator::Generate(this->m_enemies_, 5);

	this->m_player_.Restart();
}

void av::state::GameState::HandleCollision()
{
	//NOTE: Can't use an iterator and delete the elements as I go. Maybe save their position and erase them afterwards ?
	std::vector<int> bullets_to_remove;
	std::vector<int> enemies_to_remove;

	// Check if any bullet collides with enemies, then erase them from screen
	for (auto bullet_it = this->m_player_.m_bullets.begin(); bullet_it != this->m_player_.m_bullets.end(); bullet_it++)
	{
		for (auto enemies_it = this->m_enemies_.begin(); enemies_it != this->m_enemies_.end(); enemies_it++)
		{
			if (enemies_it->Collide(*bullet_it))
			{   
				//Bullet collided with Enemy
				bullets_to_remove.push_back(bullet_it - this->m_player_.m_bullets.begin());

				if (!enemies_it->IsAlive())
				{	
					//Enemy died, erase it
					enemies_to_remove.push_back(enemies_it - this->m_enemies_.begin());

					//TODO: Add points to scoreboard
					//NOTE: Maybe enemies can drop 'powerups' on death ?
				}
			}
		}
	}
	this->RemoveElements(this->m_player_.m_bullets, bullets_to_remove);
	this->RemoveElements(this->m_enemies_, enemies_to_remove);
}

//TODO: Add this List Extensions
template <class T, class Y>
void av::state::GameState::RemoveElements(std::vector<T>& vec, std::vector<Y> index)
{
	for (auto it = index.begin(); it != index.end(); it++)
	{
		vec.erase(vec.begin() + static_cast<int>(*it));
	}
}
