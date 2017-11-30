#include "GameState.hpp"
#include "../Locator.hpp"
#include "../Levels/Tutorial.hpp"

av::GameState::GameState(const sf::Vector2f l_window_size) 
: State(l_window_size), m_cursor_(), m_level_manager_()
{
	//Level Manager Setup
	this->m_level_manager_.RegisterObserver(
		EventType::Level::RESTART, std::bind(&GameState::RestartCurrentLevel, this));

	this->m_current_level_ = new Tutorial();
	this->m_current_level_->SetLevelManager(&this->m_level_manager_);
}

void av::GameState::Update(const float timestep)
{
	this->m_current_level_->Update(timestep);
}

void av::GameState::Render(sf::RenderWindow& l_window)
{
	this->m_current_level_->Render(l_window);

	this->m_cursor_.Render(l_window);
}

void av::GameState::HandleInput(sf::Event& l_event)
{
	this->m_current_level_->HandleInput(l_event);

	if(l_event.type == sf::Event::LostFocus) 
	{
		this->GetStateManager()->Notify(EventType::State::PAUSE);
		this->m_current_level_->Pause();
	}

	if(l_event.type == sf::Event::EventType::KeyPressed)
	{
		if(l_event.key.code == sf::Keyboard::Key::Escape) {
			this->GetStateManager()->Notify(EventType::State::PAUSE);
			this->m_current_level_->Pause();
		}
	}

	if(l_event.type == sf::Event::EventType::MouseMoved)
	{
		const auto mouse_position = sf::Vector2f(l_event.mouseMove.x, l_event.mouseMove.y);

		this->m_cursor_.SetPosition(mouse_position); //TODO: Add overload for float x,y
	}
}

void av::GameState::Restart()
{
	//TODO
	delete this->m_current_level_; //NOTE: No ideia if should be doing this here. I think not. Need to research this.
	this->m_current_level_ = new Tutorial();
	this->m_current_level_->SetLevelManager(&this->m_level_manager_);
}

void av::GameState::RestartCurrentLevel()
{
	this->m_current_level_->Restart();
}
