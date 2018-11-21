#include "MenuState.h"

#include <SFML/Window.hpp>

#define BUTTON_MARGIN 25.f

using namespace av;

MenuState::MenuState(const sf::Vector2f l_windowSize) :
	State(l_windowSize),
	m_NewGameButton(sf::Vector2f(), sf::Vector2f(), sf::Color::Green),
	m_HighScoreButton(sf::Vector2f(), sf::Vector2f(), sf::Color::Green),
	m_QuitGameButton(sf::Vector2f(), sf::Vector2f(), sf::Color::Green)
{
	Locator::GetLogger(INFO) << "Resolution -> " << GetWindowSize().x << " " << GetWindowSize().y << "\n";

	this->InitializeUI();
}

void MenuState::Update(float timestep)
{

}

void MenuState::Render(sf::RenderWindow& l_window)
{
	l_window.draw(this->m_Background);
	this->m_NewGameButton.Render(l_window);
	this->m_HighScoreButton.Render(l_window);
	this->m_QuitGameButton.Render(l_window);
}

void MenuState::HandleInput(sf::Event& l_event)
{
	// Check if the event, was a keyboard event
	if (l_event.type == sf::Event::EventType::KeyPressed)
	{
		Locator::GetLogger(DEBUG) << "Pressed " << l_event.key.code << "\n";

		if (l_event.key.code == sf::Keyboard::Key::Space  // Space or Enter pressed
			|| l_event.key.code == sf::Keyboard::Key::Return)
		{
			switch (this->m_VirtualIndex)
			{
			case 0: GetStateManager()->Notify(EventType::State::GAME); break;
			case 1: GetStateManager()->Notify(EventType::State::HIGHSCORE); break;
			case 2: GetStateManager()->Notify(EventType::State::EXIT); break;
			default: break;
			}
		}
		else if (l_event.key.code == sf::Keyboard::Key::Escape)
		{
			GetStateManager()->Notify(EventType::State::EXIT);
		}
		else
		{
			switch (l_event.key.code)
			{
			case sf::Keyboard::Key::Down:
			case sf::Keyboard::Key::S:
				this->HandleArrowSelection(1);
				break;
			case sf::Keyboard::Key::Up:
			case sf::Keyboard::Key::W:
				this->HandleArrowSelection(-1);
				break;
			default: /* ignored */ break;
			}
		}
	}
	else if (l_event.type == sf::Event::EventType::MouseButtonPressed)      // Mouse
	{
		const auto mouse_position = sf::Vector2f(l_event.mouseButton.x, l_event.mouseButton.y);

		if (l_event.mouseButton.button == sf::Mouse::Button::Left) // Left Click
		{
			this->HandleMouseClick(mouse_position);
		}
	}
}

void MenuState::HandleArrowSelection(const int l_direction)
{
	if (this->m_VirtualIndex + l_direction <= 0)
	{
		this->m_VirtualIndex = 0;
	}
	else if (this->m_VirtualIndex + l_direction >= 2)
	{
		this->m_VirtualIndex = 2;
	}
	else
	{
		this->m_VirtualIndex += l_direction;
	}

	std::cout << this->m_VirtualIndex << std::endl;
}

void MenuState::HandleMouseClick(const sf::Vector2f& l_mouse_position)
{
	if (this->m_NewGameButton.GetGlobalBounds().contains(l_mouse_position)) {
		Locator::GetLogger(DEBUG) << "Pressed New Game" << "\n";
		this->GetStateManager()->Notify(EventType::State::GAME);
	}
	else if (this->m_HighScoreButton.GetGlobalBounds().contains(l_mouse_position)) {
		Locator::GetLogger(DEBUG) << "Pressed HighScores" << "\n";
		this->GetStateManager()->Notify(EventType::State::HIGHSCORE);
	}
	else if (this->m_QuitGameButton.GetGlobalBounds().contains(l_mouse_position)) {
		Locator::GetLogger(DEBUG) << "Pressed Exit" << "\n";
		this->GetStateManager()->Notify(EventType::State::EXIT);
	}
}

void MenuState::InitializeUI()
{
	//Background Layer Setup
	m_Background.setFillColor(sf::Color::Blue);
	m_Background.setOutlineColor(sf::Color::Green);
	m_Background.setOutlineThickness(5.f);
	m_Background.setSize(sf::Vector2f(GetWindowSize().x * 0.35f, GetWindowSize().y * 0.45f));

	const auto background_position = sf::Vector2f(
		GetWindowSize().x / 2 - m_Background.getGlobalBounds().width / 2,
		GetWindowSize().y / 2 - m_Background.getGlobalBounds().height / 2);

	m_Background.setPosition(background_position);

	//Buttons Layer Setup
	m_NewGameButton.SetSize(sf::Vector2f(GetWindowSize().x * 0.25f, GetWindowSize().y * 0.1f));
	m_HighScoreButton.SetSize(sf::Vector2f(GetWindowSize().x * 0.25f, GetWindowSize().y * 0.1f));
	m_QuitGameButton.SetSize(sf::Vector2f(GetWindowSize().x * 0.25f, GetWindowSize().y * 0.1f));

	const auto new_game_position = sf::Vector2f(
		GetWindowSize().x / 2 - m_NewGameButton.GetGlobalBounds().width / 2,
		GetWindowSize().y / 2 - m_NewGameButton.GetGlobalBounds().height / 2 - m_HighScoreButton.GetGlobalBounds().height - BUTTON_MARGIN);

	const auto high_scores_position = sf::Vector2f(
		GetWindowSize().x / 2 - m_HighScoreButton.GetGlobalBounds().width / 2,
		GetWindowSize().y / 2 - m_HighScoreButton.GetGlobalBounds().height / 2);

	const auto quit_game_position = sf::Vector2f(
		GetWindowSize().x / 2 - m_QuitGameButton.GetGlobalBounds().width / 2,
		GetWindowSize().y / 2 - m_QuitGameButton.GetGlobalBounds().height / 2 + m_HighScoreButton.GetGlobalBounds().height + BUTTON_MARGIN);


	m_NewGameButton.SetPosition(new_game_position);
	m_NewGameButton.SetText("New Game");

	m_HighScoreButton.SetText("Highscores");
	m_HighScoreButton.SetPosition(high_scores_position);

	m_QuitGameButton.SetText("Exit");
	m_QuitGameButton.SetPosition(quit_game_position);
}