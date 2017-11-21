#include "Game.hpp"

av::Game::Game(const std::string window_title) : 
	m_window_(sf::VideoMode(800, 600, 32), window_title, sf::Style::Titlebar | sf::Style::Close)
{
	m_clock_.restart();
	m_elapsed_ = 0.0f;
	m_window_.setFramerateLimit(60);
}


av::Game::~Game()
{

}

void av::Game::Update(const float timestep)
{
	this->m_game_state_.Update(timestep);
}

void av::Game::Render()
{
	this->m_window_.clear(sf::Color(sf::Color(150, 207, 234)));
	this->m_game_state_.Render(this->m_window_);
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

void av::Game::RestartClock()
{
	this->m_elapsed_ += m_clock_.restart().asSeconds();
}

sf::RenderWindow* av::Game::GetWindow()
{
	return &this->m_window_;
}


