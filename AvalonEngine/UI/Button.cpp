#include "Button.hpp"


av::ui::Button::Button(const sf::Vector2f l_size, const sf::Vector2f l_position, const sf::String l_title)
	: m_background_(l_size),
	m_click_callback_(nullptr), m_enter_callback_(nullptr), m_exit_callback_(nullptr)
{
	m_font_.loadFromFile("titillium.otf");
	m_text_.setFont(m_font_);
	m_text_.setString(l_title);
	m_text_.setCharacterSize(30);
	m_text_.setFillColor(sf::Color::Black);
	m_text_.setPosition(l_position.x + (l_size.x - m_text_.getLocalBounds().width) / 2, l_position.y + l_size.y / 2 - m_text_.getLocalBounds().height);

	m_background_.setOutlineColor(sf::Color::White);
	m_background_.setOutlineThickness(5.f);
	m_background_.setFillColor(sf::Color::Red);
	m_background_.setPosition(l_position);
}

void av::ui::setFont(sf::Font l_font)
{
	this->m_text_.setFont(l_font);
}
void av::ui::setTextSize(Uint32 l_size)
{
	this->m_text_.setCharacterSize(l_size);
}
void av::ui::setText(sf::String l_text)
{
	this->m_text_.setString(l_text);
}
void av::ui::setTextColor(sf::Color l_color)
{
	this->m_text_.setFillColor(l_color);
}
void av::ui::setTextBackgroundColor(sf::Color l_color)
{
	this->m_text_.setOutlineColor(l_color); //NOTE: Not sure if this is valid
}

void av::ui::setBackgroundColor()
{

}
void av::ui::setBackgroundOutlineColor()
{

}
void av::ui::setBackgroundOutlineThickness()
{

}

void av::ui::setOnClick(events::MouseClickCallback* l_callback)
{
	this->m_click_callback_ = l_callback;
}
void av::ui::setOnMouseEnter(events::MouseOverEnterCallback* l_callback)
{
	this->m_enter_callback_ = l_callback;
}
void av::ui::setOnMouseExit(events::MouseOverExitCallback* l_callback)
{
	this->m_exit_callback_ = l_callback;
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
	l_window.draw(this->m_background_);
	l_window.draw(this->m_text_);
}

sf::FloatRect av::ui::Button::GetGlobalBounds()
{
	return this->m_background_.getGlobalBounds();
}


