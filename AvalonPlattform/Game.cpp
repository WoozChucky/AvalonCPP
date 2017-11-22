#include "Game.hpp"

av::Game::Game(const std::string window_title) : 
	m_game_state_(),
	m_menu_state_(),
	m_window_(sf::VideoMode(800, 600, 32), window_title, sf::Style::Titlebar | sf::Style::Close)
{
	Restart();
}

av::Game::~Game()
{

}

void av::Game::Update(const float timestep)
{
	this->m_current_state_->Update(timestep);

	if(this->m_current_state_ == &this->m_menu_state_)
	{
		if(this->m_menu_state_.getButtonPressed(0))
		{
			this->Restart();
			this->m_menu_state_.setButtonPressed(0, false);
		} 
		else if (this->m_menu_state_.getButtonPressed(1))
		{
			// TODO: Highscore states
		}
		else if (this->m_menu_state_.getButtonPressed(2))
		{
			this->m_window_.close();
			this->m_menu_state_.setButtonPressed(2, false);
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
		if (sf::Event::EventType::Closed == event.type)
		{
			this->m_window_.close();
		}
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
	this->m_game_state_.Restart();
}

void av::Game::RestartClock()
{
	this->m_elapsed_ += m_clock_.restart().asSeconds();
}

void av::Game::ChangeState(av::state::State* l_state)
{
	this->m_current_state_ = l_state;
}

sf::RenderWindow* av::Game::GetWindow()
{
	return &this->m_window_;
}

