#include "MenuState.hpp"

av::state::MenuState::MenuState() :
	m_new_game_(sf::Vector2f(200.f, 100.f), sf::Vector2f(300.f, 120.f), sf::String("New Game")),
	m_high_scores_(sf::Vector2f(200.f, 100.f), sf::Vector2f(300.f, 250.f), sf::String("High Scores")),
	m_quit_game_(sf::Vector2f(200.f, 100.f), sf::Vector2f(300.f, 380.f), sf::String("Quit Game")), 
	m_pressed_(false)
{
	m_background_.setPosition(sf::Vector2f(270.f, 90.f));
	m_background_.setFillColor(sf::Color::Blue);
	m_background_.setOutlineColor(sf::Color::Black);
	m_background_.setOutlineThickness(2.f);
	m_background_.setSize(sf::Vector2f(260.f, 420.f));

	for (auto i = 0; i < 3; i++)
	{
		m_button_pressed_[i] = false;
	}
}

av::state::MenuState::~MenuState()
{
}

void av::state::MenuState::Update(float timestep)
{
	auto temp{ 0 };
	if (m_pressed_) {
		if (m_new_game_.GetGlobalBounds().contains(m_mouse_position_.x, m_mouse_position_.y)) {
			m_button_pressed_[0] = true;
			temp = 0;
		}
		else if (m_high_scores_.GetGlobalBounds().contains(m_mouse_position_.x, m_mouse_position_.y)) {
			m_button_pressed_[1] = true;
			temp = 1;
		}
		else if (m_quit_game_.GetGlobalBounds().contains(m_mouse_position_.x, m_mouse_position_.y)) {
			m_button_pressed_[2] = true;
			temp = 2;
		}
		m_pressed_ = false;
	}
}

void av::state::MenuState::Render(sf::RenderWindow& l_window)
{
	l_window.draw(m_background_);
	m_new_game_.Render(l_window);
	m_high_scores_.Render(l_window);
	m_quit_game_.Render(l_window);
}

void av::state::MenuState::HandleInput()
{
}

void av::state::MenuState::setPressed(bool l_status)
{
	this->m_pressed_ = l_status;
}

bool av::state::MenuState::getPressed()
{
	return this->m_pressed_;
}

void av::state::MenuState::setMousePosition(const sf::Vector2i l_position)
{
	//TODO
}
sf::Vector2i av::state::MenuState::getMousePosition() 
{
	sf::Vector2i o(0, 0);
	return o;
}

void av::state::MenuState::setButtonPressed(int l_index, int l_value)
{
	this->m_button_pressed_[l_index] = l_value;
}

int av::state::MenuState::getButtonPressed(int l_index)
{
	return this->m_button_pressed_[l_index];
}
