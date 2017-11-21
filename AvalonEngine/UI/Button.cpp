#include "Button.hpp"


av::ui::Button::Button(const sf::Vector2f l_size, const sf::Vector2f l_position, const sf::String l_title)
	: m_click_callback_(nullptr), m_enter_callback_(nullptr), m_exit_callback_(nullptr)
{
	m_font_.loadFromFile("titillium.otf");
	m_text_.setFont(m_font_);
	m_text_.setString(l_title);
	m_text_.setCharacterSize(30);
	m_text_.setPosition(l_position.x + (l_size.x - m_text_.getLocalBounds().width) / 2, l_position.y + l_size.y / 2 - m_text_.getLocalBounds().height);

	m_background_.setOutlineColor(sf::Color::Black);
	m_background_.setOutlineThickness(2.f);
	m_background_.setFillColor(sf::Color::Green);
	m_background_.setPosition(l_position);
}

void av::ui::Button::setText(const sf::String l_text)
{
	this->m_text_.setString(l_text);
}

void av::ui::Button::setOnClick(events::MouseClickCallback* l_callback)
{
	this->m_click_callback_ = l_callback;
}

void av::ui::Button::onClick() const
{
	if(this->m_click_callback_ != nullptr)
	{
		this->m_click_callback_->Execute();
	} 
	else
	{
		throw "callback is nullptr";
	}
}

void av::ui::Button::Update(float timestep)
{
}

void av::ui::Button::Render(sf::RenderWindow& l_window)
{
	l_window.draw(m_background_);
	l_window.draw(m_text_);
}

sf::FloatRect av::ui::Button::GetGlobalBounds()
{
	return this->m_background_.getGlobalBounds();
}


