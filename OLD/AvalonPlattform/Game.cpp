#include "Game.hpp"

av::Game::Game(const fs::Configuration l_cfg, const std::string& window_title) :
	m_game_state_(sf::Vector2f(l_cfg.video_l.Width, l_cfg.video_l.Height)),
	m_menu_state_(sf::Vector2f(l_cfg.video_l.Width, l_cfg.video_l.Height)),
	m_pause_state_(sf::Vector2f(l_cfg.video_l.Width, l_cfg.video_l.Height)),
	m_state_manager_(),
	m_window_(sf::VideoMode(l_cfg.video_l.Width, l_cfg.video_l.Height, l_cfg.video_l.Bpp), window_title, sf::Style::Titlebar | sf::Style::Close)
{
	this->m_clock_.restart();
	this->m_elapsed_ = 0.0f;
	this->m_window_.setFramerateLimit(90);
	this->m_current_state_ = &this->m_menu_state_;
	this->m_previous_state_ = nullptr;

	// Register Observers
	this->m_state_manager_.RegisterObserver(
		EventType::State::GAME, std::bind(&Game::Restart, this));
	this->m_state_manager_.RegisterObserver(
		EventType::State::MENU, std::bind(&Game::ChangeState, this, &this->m_menu_state_));
	this->m_state_manager_.RegisterObserver(
		EventType::State::PAUSE, std::bind(&Game::ChangeState, this, &this->m_pause_state_));
	//this->m_state_manager_.RegisterObserver(
	//	EventType::State::HIGHSCORE, std::bind(&Game::ChangeState, this, &this->m_game_state_));
	this->m_state_manager_.RegisterObserver(
		EventType::State::PREVIOUS, std::bind(&Game::PreviousState, this));
	this->m_state_manager_.RegisterObserver(
		EventType::State::EXIT, std::bind(&Game::Exit, this));
	
	// Pass StateManager to States
	this->m_menu_state_.SetStateManager(&this->m_state_manager_);
	this->m_game_state_.SetStateManager(&this->m_state_manager_);
	this->m_pause_state_.SetStateManager(&this->m_state_manager_);
}

void av::Game::Update(const float timestep) const
{
	// Handle updates for current state
	this->m_current_state_->Update(timestep);
}

void av::Game::Render()
{
	this->m_window_.clear(sf::Color(sf::Color(150, 207, 234)));
	// Render the current state
	this->m_current_state_->Render(this->m_window_);
	this->m_window_.display();
}

void av::Game::HandleInput()
{
	sf::Event event{};

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

void av::Game::Run() //This the default game loop
{
	//NOTE: Analyze if this timestep doesn't fuck up when we have dropped frames.

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

void av::Game::ChangeState(State* l_state)
{
	//NOTE: The mouse visibility should change depending on the current state.
	// Probably the cursor will be a part of of the State.hpp and we'll hande it there later.
	this->m_previous_state_ = m_current_state_;
	this->m_current_state_ = l_state;

	this->m_window_.setMouseCursorVisible(typeid(this->m_current_state_) != typeid(GameState));

	Locator::GetLogger() << __FUNCTION__ << "State was changed";
}

void av::Game::Exit()
{
	Locator::GetLogger() << __FUNCTION__ << "Shutting down";
	this->m_window_.close();
}

void av::Game::PreviousState()
{
	this->ChangeState(this->m_previous_state_);
	/*
	this->m_current_state_ = this->m_previous_state_;

	this->m_window_.setMouseCursorVisible(typeid(this->m_current_state_) != typeid(GameState));

	Locator::GetLogger().Log(__FUNCTION__, "Going back to previous state");
	 */
}