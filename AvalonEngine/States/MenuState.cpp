#include "MenuState.hpp"

av::state::MenuState::MenuState() :
	m_new_game_(sf::Vector2f(200.f, 100.f), sf::Vector2f(300.f, 120.f), sf::Color::Green),
	m_high_scores_(sf::Vector2f(200.f, 100.f), sf::Vector2f(300.f, 250.f), sf::Color::Green),
	m_quit_game_(sf::Vector2f(200.f, 100.f), sf::Vector2f(300.f, 380.f), sf::Color::Green),
	m_new(false), m_high(false), m_exit(false)
{
	m_background_.setPosition(sf::Vector2f(270.f, 90.f));
	m_background_.setFillColor(sf::Color::Blue);
	m_background_.setOutlineColor(sf::Color::Black);
	m_background_.setOutlineThickness(5.f);
	m_background_.setSize(sf::Vector2f(260.f, 420.f));

	m_new_game_.setText("New Game");
	m_high_scores_.setText("Highscores");
	m_quit_game_.setText("Exit");
}

void av::state::MenuState::Update(float timestep)
{
	
}

void av::state::MenuState::Render(sf::RenderWindow& l_window)
{
	l_window.draw(this->m_background_);
	this->m_new_game_.Render(l_window);
	this->m_high_scores_.Render(l_window);
	this->m_quit_game_.Render(l_window);
}

void av::state::MenuState::HandleInput(const sf::Event l_event)
{
	// Check if the event, was a keyboard event
	if (l_event.type == sf::Event::EventType::KeyPressed)
	{
		std::cout << "Pressed " << l_event.key.code << std::endl;

		if (l_event.key.code == sf::Keyboard::Key::Space  // Space or Enter pressed
			|| l_event.key.code == sf::Keyboard::Key::Return)
		{
			switch (this->m_virtual_index_)
			{
			case 0: this->m_new = true; break;
			case 1: this->m_high = true; break;
			case 2: this->m_exit = true; break;
			default: break;
			}
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

void av::state::MenuState::HandleArrowSelection(const int l_direction)
{
	if(this->m_virtual_index_ + l_direction <= 0)
	{
		this->m_virtual_index_ = 0;
	}
	else if (this->m_virtual_index_ + l_direction >= 2)
	{
		this->m_virtual_index_ = 2;
	}
	else
	{
		this->m_virtual_index_ += l_direction;
	}

	std::cout << this->m_virtual_index_ << std::endl;
}

void av::state::MenuState::HandleMouseClick(const sf::Vector2f& l_mouse_position)
{
	if (m_new_game_.GetGlobalBounds().contains(l_mouse_position)) {
		std::cout << "Pressed New Game" << std::endl;
		this->m_new = true;
	}
	else if (m_high_scores_.GetGlobalBounds().contains(l_mouse_position)) {
		std::cout << "Pressed Highscores" << std::endl;
		this->m_high = true;
	}
	else if (m_quit_game_.GetGlobalBounds().contains(l_mouse_position)) {
		std::cout << "Pressed Exit" << std::endl;
		this->m_exit = true;
	}
}
