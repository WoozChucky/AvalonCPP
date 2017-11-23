#include "PauseState.hpp"

av::state::PauseState::PauseState() :
    m_continue_game_(sf::Vector2f(200.f, 100.f), sf::Vector2f(300.f, 250.f), sf::Color::Yellow),
    m_options_(sf::Vector2f(200.f, 100.f), sf::Vector2f(300.f, 350.f), sf::Color::Yellow),
    m_quit_game_(sf::Vector2f(200.f, 100.f), sf::Vector2f(300.f, 450.f), sf::Color::Yellow)
{
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

av::state::PauseState::~PauseState()
{
    
}

void av::state::PauseState::Update(float timestep)
{

}

void av::state::PauseState::Render(sf::RenderWindow& l_window)
{
    this->m_continue_game_.Render(l_window);
    this->m_options_.Render(l_window);
    this->m_quit_game_.Render(l_window);
}

void av::state::PauseState::HandleInput(sf::Event l_event)
{
    if(l_event.type == sf::Event::EventType::KeyPressed)
	{
		if(l_event.key.code == sf::Keyboard::Key::Escape) {
			this->m_exit_pause_ = true;
		}
	}
}