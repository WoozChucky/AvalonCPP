#include "PauseState.h"

using namespace av;

PauseState::PauseState(const sf::Vector2f l_windowSize)
	: State(l_windowSize),
	m_ContinueGameButton(sf::Vector2f(), sf::Vector2f(), sf::Color::Yellow),
	m_OptionsButton(sf::Vector2f(), sf::Vector2f(), sf::Color::Yellow),
	m_QuitGameButton(sf::Vector2f(), sf::Vector2f(), sf::Color::Yellow)
{
	this->InitializeUI();
}

void PauseState::Update(float timestep)
{

}

void PauseState::Render(sf::RenderWindow& l_window)
{
	l_window.draw(this->m_TitleText);
	this->m_ContinueGameButton.Render(l_window);
	this->m_OptionsButton.Render(l_window);
	this->m_QuitGameButton.Render(l_window);
}

void PauseState::HandleInput(sf::Event& l_event)
{
	// Check if the event, was a keyboard event
	if (l_event.type == sf::Event::EventType::KeyPressed)
	{
		if (l_event.key.code == sf::Keyboard::Key::Escape) { //Escape pressed
			this->GetStateManager()->Notify(EventType::State::PREVIOUS);
		}
		else if (l_event.key.code == sf::Keyboard::Key::Space  // Space or Enter pressed
			|| l_event.key.code == sf::Keyboard::Key::Return)
		{
			//TODO: Handle Logic for selected option/button
			std::cout << "Pressed " << l_event.key.code << std::endl;
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

void PauseState::HandleMouseClick(const sf::Vector2f l_mouse_position)
{
	// Continue was clicked ?
	if (this->m_ContinueGameButton.GetGlobalBounds().contains(l_mouse_position))
	{
		this->GetStateManager()->Notify(EventType::State::PREVIOUS);
	}

	// Options was clicked ?
	if (this->m_OptionsButton.GetGlobalBounds().contains(l_mouse_position))
	{
		this->GetStateManager()->Notify(EventType::State::OPTIONS);
	}

	// Quit Game was clicked ?
	if (this->m_QuitGameButton.GetGlobalBounds().contains(l_mouse_position))
	{
		this->GetStateManager()->Notify(EventType::State::MENU);
	}
}

void PauseState::InitializeUI()
{
	m_Font.loadFromFile("Assets/Fonts/titillium.otf");
	m_TitleText.setFont(m_Font);
	m_TitleText.setString("Pause");
	m_TitleText.setCharacterSize(40);
	m_TitleText.setStyle(sf::Text::Bold);
	m_TitleText.setFillColor(sf::Color::Black);
	m_TitleText.setPosition(GetWindowSize().x / 2 - m_TitleText.getGlobalBounds().width / 2, GetWindowSize().y * 0.1f);

	m_ContinueGameButton.SetSize(sf::Vector2f(GetWindowSize().x * 0.25f, GetWindowSize().y * 0.1f));
	m_OptionsButton.SetSize(sf::Vector2f(GetWindowSize().x * 0.25f, GetWindowSize().y * 0.1f));
	m_QuitGameButton.SetSize(sf::Vector2f(GetWindowSize().x * 0.25f, GetWindowSize().y * 0.1f));

	const auto continue_game_position = sf::Vector2f(
		GetWindowSize().x / 2 - m_ContinueGameButton.GetGlobalBounds().width / 2,
		GetWindowSize().y / 2 - m_ContinueGameButton.GetGlobalBounds().height / 2 - m_OptionsButton.GetGlobalBounds().height);

	const auto options_position = sf::Vector2f(
		GetWindowSize().x / 2 - m_OptionsButton.GetGlobalBounds().width / 2,
		GetWindowSize().y / 2 - m_OptionsButton.GetGlobalBounds().height / 2);

	const auto quit_game_position = sf::Vector2f(
		GetWindowSize().x / 2 - m_QuitGameButton.GetGlobalBounds().width / 2,
		GetWindowSize().y / 2 - m_QuitGameButton.GetGlobalBounds().height / 2 + m_OptionsButton.GetGlobalBounds().height);

	m_ContinueGameButton.SetText("Continue");
	m_ContinueGameButton.SetPosition(continue_game_position);
	m_ContinueGameButton.SetBackgroundOutlineThickness(5.f);
	m_ContinueGameButton.SetBackgroundOutlineColor(sf::Color::Cyan);

	m_OptionsButton.SetText("Options");
	m_OptionsButton.SetPosition(options_position);
	m_OptionsButton.SetBackgroundOutlineThickness(5.f);
	m_OptionsButton.SetBackgroundOutlineColor(sf::Color::Cyan);

	m_QuitGameButton.SetText("Quit");
	m_QuitGameButton.SetPosition(quit_game_position);
	m_QuitGameButton.SetBackgroundOutlineThickness(5.f);
	m_QuitGameButton.SetBackgroundOutlineColor(sf::Color::Cyan);
}
