#include "PauseState.hpp"

av::state::PauseState::PauseState() :
    m_continue_game_(sf::Vector2f(200.f, 100.f), sf::Vector2f(300.f, 250.f), sf::Color::Yellow),
    m_options_(sf::Vector2f(200.f, 100.f), sf::Vector2f(300.f, 350.f), sf::Color::Yellow),
    m_quit_game_(sf::Vector2f(200.f, 100.f), sf::Vector2f(300.f, 450.f), sf::Color::Yellow)
{
	m_font_.loadFromFile("titillium.otf");
	m_title_.setFont(m_font_);
	m_title_.setString("Pause");
	m_title_.setCharacterSize(40);
	m_title_.setStyle(sf::Text::Bold);
	m_title_.setFillColor(sf::Color::Black);

    m_continue_game_.setText("Continue");
    m_continue_game_.setBackgroundOutlineThickness(5.f);
    m_continue_game_.setBackgroundOutlineColor(sf::Color::Cyan);

    m_options_.setText("Options");
    m_options_.setBackgroundOutlineThickness(5.f);
    m_options_.setBackgroundOutlineColor(sf::Color::Cyan);

    m_quit_game_.setText("Quit");
    m_quit_game_.setBackgroundOutlineThickness(5.f);
    m_quit_game_.setBackgroundOutlineColor(sf::Color::Cyan);
}

void av::state::PauseState::Update(float timestep)
{
	//TODO(Nuno): This should not be done here. Find a better way to do it.
	this->m_title_.setPosition(m_window_size.x / 2 - m_title_.getGlobalBounds().width / 2, 50.f);
}

void av::state::PauseState::Render(sf::RenderWindow& l_window)
{
	l_window.draw(this->m_title_);
    this->m_continue_game_.Render(l_window);
    this->m_options_.Render(l_window);
    this->m_quit_game_.Render(l_window);
}

void av::state::PauseState::HandleInput(const sf::Event l_event)
{
    // Check if the event, was a keyboard event
    if(l_event.type == sf::Event::EventType::KeyPressed)
	{
		if(l_event.key.code == sf::Keyboard::Key::Escape) { //Escape pressed
			this->m_exit_pause_ = true;
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

void av::state::PauseState::HandleMouseClick(const sf::Vector2f l_mouse_position)
{    
    if(this->m_continue_game_.GetGlobalBounds().contains(l_mouse_position))
    {
        // Continue was clicked
        this->m_exit_pause_ = true;
    } 
    else if (this->m_options_.GetGlobalBounds().contains(l_mouse_position))
    {
        // Options was clicked
    }
    else if(this->m_quit_game_.GetGlobalBounds().contains(l_mouse_position))
    {
        // Quit Game was clicked
        this->m_exit_game_ = true;
    }
}