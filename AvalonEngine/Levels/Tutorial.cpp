#include "Tutorial.hpp"
#include "../Extensions/VectorExtensions.hpp"
#include "../Generators/EntityGenerator.hpp"

av::Tutorial::Tutorial()
    : Level(sf::Vector2f(0.f, 0.f)), m_player_()
{

}

void av::Tutorial::Update(float timestep)
{
    // Update player status
	this->m_player_.Update(timestep);

    //Spawn Enemy if we have less than 5 on screen.
	EntityGenerator::Generate<Enemy>(this->m_enemies_, 5);

	this->ResolveCollision(this->m_player_, this->m_enemies_[0]);
}

void av::Tutorial::HandleInput(sf::Event& l_event)
{
    this->m_player_.HandleInput(l_event);

    if(l_event.type == sf::Event::EventType::KeyPressed)
	{
		if(l_event.key.code == sf::Keyboard::Key::R) {
			this->GetLevelManager()->Notify(EventType::Level::RESTART);
		}
	}
}

void av::Tutorial::Render(sf::RenderWindow& l_window)
{
    this->m_player_.Render(l_window);

    for (auto i = 0; i < this->m_enemies_.size(); i++)
	{
		this->m_enemies_.at(i).Render(l_window);
	}
}

void av::Tutorial::Pause()
{

}

void av::Tutorial::Resume()
{
    
}

void av::Tutorial::Restart()
{
    this->m_player_.Restart();

    this->m_enemies_.clear();
	
	EntityGenerator::Generate(this->m_enemies_, 5);
}

void av::Tutorial::ResolveCollision(Player& l_player, Enemy& l_enemy)
{
	//NOTE: Can't use an iterator and delete the elements as I go. Maybe save their position and erase them afterwards ?
	std::vector<int> bullets_to_remove;
	std::vector<int> enemies_to_remove;

	// Check if any bullet collides with enemies, then erase them from screen
	for (auto bullet_it = this->m_player_.m_bullets_.begin(); bullet_it != this->m_player_.m_bullets_.end(); bullet_it++)
	{
		for (auto enemies_it = this->m_enemies_.begin(); enemies_it != this->m_enemies_.end(); enemies_it++)
		{
			if (enemies_it->Collide(*bullet_it))
			{   
				//Bullet collided with Enemy
				bullets_to_remove.push_back(bullet_it - this->m_player_.m_bullets_.begin());

				if (!enemies_it->IsAlive())
				{	
					Locator::GetAudio().PlaySFX(audio::SFX::BASIC_ENEMY_DIE);

					//Enemy died, erase it
					enemies_to_remove.push_back(enemies_it - this->m_enemies_.begin());

					//TODO: Add points to scoreboard
					//NOTE: Maybe enemies can drop 'powerups' on death ?
				}
			}
		}
	}	

	VectorExtensions::RemoveElements(this->m_player_.m_bullets_, bullets_to_remove);
	VectorExtensions::RemoveElements(this->m_enemies_, enemies_to_remove);
}