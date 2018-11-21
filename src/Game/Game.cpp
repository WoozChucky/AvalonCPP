#include "Game.h"

#include <SFML/Window/Event.hpp>

using namespace av;

Game::Game(const fs::Configuration l_cfg, const std::string& l_window_title)
  : m_Window(sf::VideoMode(l_cfg.video.Width, l_cfg.video.Height, l_cfg.video.Bpp), l_window_title, sf::Style::Titlebar | sf::Style::Close),
	m_DebugView(sf::FloatRect(0.f, 0.f, 200, 200)),
	m_Elapsed(0.0f),
	m_MenuState(sf::Vector2f(static_cast<float>(l_cfg.video.Width), static_cast<float>(l_cfg.video.Height))),
	m_GameState(sf::Vector2f(static_cast<float>(l_cfg.video.Width), static_cast<float>(l_cfg.video.Height))),
	m_PauseState(sf::Vector2f(static_cast<float>(l_cfg.video.Width), static_cast<float>(l_cfg.video.Height))),
	m_CurrentState(&m_MenuState),
	m_PreviousState(nullptr)
{
	this->m_AppIcon.loadFromFile("Assets/Textures/icon.png");

	this->m_Window.setIcon(this->m_AppIcon.getSize().x, this->m_AppIcon.getSize().y, this->m_AppIcon.getPixelsPtr());
	this->m_Window.setVerticalSyncEnabled(false);
	this->m_Window.setFramerateLimit(60);

	this->m_Clock.restart();

	// Register observers
	this->m_StateManager.RegisterObserver(EventType::State::GAME, std::bind(&Game::Restart, this));
	this->m_StateManager.RegisterObserver(EventType::State::MENU, std::bind(&Game::ChangeState, this, &this->m_MenuState));
	this->m_StateManager.RegisterObserver(EventType::State::PAUSE, std::bind(&Game::ChangeState, this, &this->m_PauseState));
	this->m_StateManager.RegisterObserver(EventType::State::PREVIOUS, std::bind(&Game::PreviousState, this));
	this->m_StateManager.RegisterObserver(EventType::State::EXIT, std::bind(&Game::Exit, this));

	// Pass StateManager to specific States
	this->m_MenuState.SetStateManager(&this->m_StateManager);
	this->m_GameState.SetStateManager(&this->m_StateManager);
	this->m_PauseState.SetStateManager(&this->m_StateManager);
}

void Game::Update(const float timestep) const
{
	// Handle updates for current state
	this->m_CurrentState->Update(timestep);
}

void Game::Render()
{
	this->m_Window.clear(sf::Color(sf::Color(150, 207, 234)));
	// Render the current state
	this->m_CurrentState->Render(this->m_Window);
	this->m_Window.display();
}

void Game::HandleInput()
{
	sf::Event event{};

	while (this->m_Window.pollEvent(event))
	{
		// Window Event
		if (sf::Event::EventType::Closed == event.type)
		{
			this->m_Window.close(); // Make sure to release all resources with .close();
		}

		// Handle input for current state
		this->m_CurrentState->HandleInput(event);
	}
}

void Game::Run()
{
	const auto timestep = 1.0f / 60.0f;

	while (this->m_Window.isOpen())
	{
		this->HandleInput();

		while (this->m_Elapsed >= timestep)
		{
			this->Update(timestep);
			this->m_Elapsed -= timestep;
		}
		this->Render();
		this->RestartClock();
	}
}

void Game::Restart()
{
	this->m_Clock.restart();
	this->m_Elapsed = 0.0f;
	this->m_CurrentState = &this->m_GameState;
	this->m_Window.setMouseCursorVisible(true);
}

void Game::RestartClock()
{
	this->m_Elapsed += m_Clock.restart().asSeconds();
}

void Game::ChangeState(State* l_state)
{
	//NOTE: The mouse visibility should change depending on the current state.
	// Probably the cursor will be a part of of the State.hpp and we'll hande it there later.
	this->m_PreviousState = m_CurrentState;
	this->m_CurrentState = l_state;

	this->m_Window.setMouseCursorVisible(typeid(this->m_CurrentState) != typeid(GameState));

	Locator::GetLogger() << __FUNCTION__ << "State was changed";
}

void Game::Exit()
{
	Locator::GetLogger() << __FUNCTION__ << "Shutting down";
	this->m_Window.close();
}

void Game::PreviousState()
{
	this->ChangeState(this->m_PreviousState);
	/*
	this->m_current_state_ = this->m_previous_state_;

	this->m_window_.setMouseCursorVisible(typeid(this->m_current_state_) != typeid(GameState));

	Locator::GetLogger().Log(__FUNCTION__, "Going back to previous state");
	 */
}

