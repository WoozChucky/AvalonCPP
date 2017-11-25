#include "Game.hpp"

av::Game::Game(const sf::Uint32 l_width, const sf::Uint32 l_height, const std::string window_title) :
	m_game_state_(),
	m_menu_state_(),
	m_pause_state_(),
	m_window_(sf::VideoMode(l_width, l_height, 32), window_title, sf::Style::Titlebar | sf::Style::Close)
{
	this->m_clock_.restart();
	this->m_elapsed_ = 0.0f;
	this->m_window_.setFramerateLimit(90);
	this->m_current_state_ = &this->m_menu_state_;
	this->m_previous_state_ = nullptr;
}

void av::Game::Update(const float timestep)
{
	this->m_current_state_->Update(timestep);

	if(this->m_current_state_ == &this->m_menu_state_) // Menu State
	{
		if(this->m_menu_state_.m_new)
		{
			this->Restart();
			this->m_menu_state_.m_new = false;
		} 
		else if (this->m_menu_state_.m_high)
		{
			//TODO: Highscore states
			this->m_menu_state_.m_high = false;
		}
		else if (this->m_menu_state_.m_exit)
		{
			this->m_menu_state_.m_exit = false;
			this->m_window_.close();
		}
	}
	else if (this->m_current_state_ == &this->m_game_state_) // Game State
	{
		if(this->m_game_state_.m_requires_pause) { //TODO: Getter and Setter
			this->m_game_state_.m_requires_pause = false;
			this->ChangeState(&this->m_pause_state_);
		}
	}
	else if (this->m_current_state_ == &this->m_pause_state_) // Pause State
	{
		if(this->m_pause_state_.m_exit_pause_)
		{
			this->m_pause_state_.m_exit_pause_ = false;
			this->ChangeState(this->m_previous_state_);
		}
		else if (this->m_pause_state_.m_exit_game_)
		{
			this->m_pause_state_.m_exit_game_ = false;
			this->ChangeState(&this->m_menu_state_);
		}
	}
}

void av::Game::Render()
{
	this->m_window_.clear(sf::Color(sf::Color(150, 207, 234)));
	this->m_current_state_->Render(this->m_window_);
	this->m_window_.display();
}

void av::Game::HandleInput()
{
	sf::Event event;

	while (this->m_window_.pollEvent(event))
	{
		// Window Event
		if (sf::Event::EventType::Closed == event.type)					
		{
			this->m_window_.close(); // Make sure to release all resources with .close();
		}

		// Handle input for current state
		this->m_current_state_->HandleInput(event);
	}
}

void av::Game::Run()
{
	const auto timestep = 1.0f / 60.f;

	while (this->m_window_.isOpen())
	{
		this->HandleInput();

		while (this->m_elapsed_ >= timestep)
		{
			this->Update(timestep);
			this->m_elapsed_ -= timestep;
		}
		this->Render();
		this->RestartClock();
	}
}

void av::Game::Restart() 
{
	this->m_clock_.restart();
	this->m_elapsed_ = 0.0f;
	this->m_window_.setFramerateLimit(90);
	this->m_current_state_ = &this->m_game_state_;
	this->m_window_.setMouseCursorVisible(false);
	this->m_game_state_.Restart();
}

void av::Game::RestartClock()
{
	this->m_elapsed_ += m_clock_.restart().asSeconds();
}

void av::Game::ChangeState(state::State* l_state)
{
	//NOTE: The mouse visibility should change depending on the current state.
	// Since I still havent decided if the cursor will be the same for the entire game,
	// we're going to do some spaguetti code below to determine the visibility.
	// Probably the cursor will be a part of of the State.hpp and we'll hande it there later.

	this->m_previous_state_ = m_current_state_;
	this->m_current_state_ = l_state;
	this->m_current_state_->m_window_size = m_window_.getView().getSize();


	this->m_window_.setMouseCursorVisible(typeid(this->m_current_state_) != typeid(state::GameState));
	
}