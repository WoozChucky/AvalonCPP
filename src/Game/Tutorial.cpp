#include "Tutorial.h"

using namespace av;

Tutorial::Tutorial()
	: Level(sf::Vector2f(0.f, 0.f))
{

}

void Tutorial::Update(float timestep)
{
	
}

void Tutorial::HandleInput(sf::Event& l_event)
{
	if (l_event.type == sf::Event::EventType::KeyPressed)
	{
		if (l_event.key.code == sf::Keyboard::Key::R) {
			this->GetLevelManager()->Notify(EventType::Level::RESTART);
		}
	}
}

void Tutorial::Render(sf::RenderWindow& l_window)
{
	
}

void Tutorial::Pause()
{
	
}

void Tutorial::Restart()
{
	
}

void Tutorial::Resume()
{
	
}




