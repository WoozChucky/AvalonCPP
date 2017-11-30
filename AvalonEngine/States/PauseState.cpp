#include "PauseState.hpp"

av::PauseState::PauseState(const sf::Vector2f l_window_size) :
	State(l_window_size),
    m_continue_game_(sf::Vector2f(), sf::Vector2f(), sf::Color::Yellow),
    m_options_(sf::Vector2f(), sf::Vector2f(), sf::Color::Yellow),
    m_quit_game_(sf::Vector2f(), sf::Vector2f(), sf::Color::Yellow)
{
	this->InitializeUI();
}

void av::PauseState::Update(float timestep)
{

}

void av::PauseState::Render(sf::RenderWindow& l_window)
{
	l_window.draw(this->m_title_);
    this->m_continue_game_.Render(l_window);
    this->m_options_.Render(l_window);
    this->m_quit_game_.Render(l_window);
}

void av::PauseState::HandleInput(sf::Event& l_event)
{
    // Check if the event, was a keyboard event
    if(l_event.type == sf::Event::EventType::KeyPressed)
	{
		if(l_event.key.code == sf::Keyboard::Key::Escape) { //Escape pressed
			this->GetStateManager()->Notify(av::EventType::State::PREVIOUS);
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

        if(l_event.mouseButton.button == sf::Mouse::Button::Left) // Left Click
        {
            this->HandleMouseClick(mouse_position);
        }
	}
}

void av::PauseState::HandleMouseClick(const sf::Vector2f l_mouse_position)
{    
	// Continue was clicked ?
	if(this->m_continue_game_.GetGlobalBounds().contains(l_mouse_position))
	{
		this->GetStateManager()->Notify(av::EventType::State::PREVIOUS);
	}
    
	// Options was clicked ?
	if(this->m_options_.GetGlobalBounds().contains(l_mouse_position))
	{
		this->GetStateManager()->Notify(av::EventType::State::OPTIONS);
	}

	// Quit Game was clicked ?
	if(this->m_quit_game_.GetGlobalBounds().contains(l_mouse_position))
	{
		this->GetStateManager()->Notify(av::EventType::State::MENU);
	}
}

void av::PauseState::InitializeUI()
{
	m_font_.loadFromFile("Assets/Fonts/titillium.otf");
	m_title_.setFont(m_font_);
	m_title_.setString("Pause");
	m_title_.setCharacterSize(40);
	m_title_.setStyle(sf::Text::Bold);
	m_title_.setFillColor(sf::Color::Black);
	m_title_.setPosition(GetWindowSize().x / 2 - m_title_.getGlobalBounds().width / 2, GetWindowSize().y * 0.1f);

	m_continue_game_.SetSize(sf::Vector2f(GetWindowSize().x * 0.25f, GetWindowSize().y * 0.1f));
	m_options_.SetSize(sf::Vector2f(GetWindowSize().x * 0.25f, GetWindowSize().y * 0.1f));
	m_quit_game_.SetSize(sf::Vector2f(GetWindowSize().x * 0.25f, GetWindowSize().y * 0.1f));

	const auto continue_game_position = sf::Vector2f(
		GetWindowSize().x / 2 - m_continue_game_.GetGlobalBounds().width / 2,
		GetWindowSize().y / 2 - m_continue_game_.GetGlobalBounds().height / 2 - m_options_.GetGlobalBounds().height);

	const auto options_position = sf::Vector2f(
		GetWindowSize().x / 2 - m_options_.GetGlobalBounds().width / 2,
		GetWindowSize().y / 2 - m_options_.GetGlobalBounds().height / 2);

	const auto quit_game_position = sf::Vector2f(
		GetWindowSize().x / 2 - m_quit_game_.GetGlobalBounds().width / 2,
		GetWindowSize().y / 2 - m_quit_game_.GetGlobalBounds().height / 2 + m_options_.GetGlobalBounds().height);

	
	m_continue_game_.SetText("Continue");
	m_continue_game_.SetPosition(continue_game_position);
	m_continue_game_.SetBackgroundOutlineThickness(5.f);
	m_continue_game_.SetBackgroundOutlineColor(sf::Color::Cyan);

	m_options_.SetText("Options");
	m_options_.SetPosition(options_position);
	m_options_.SetBackgroundOutlineThickness(5.f);
	m_options_.SetBackgroundOutlineColor(sf::Color::Cyan);

	m_quit_game_.SetText("Quit");
	m_quit_game_.SetPosition(quit_game_position);
	m_quit_game_.SetBackgroundOutlineThickness(5.f);
	m_quit_game_.SetBackgroundOutlineColor(sf::Color::Cyan);
}
