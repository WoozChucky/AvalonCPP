#include "Button.h"

#include <AVMath.h>

using namespace av;

Button::Button(const sf::Vector2f l_size, const sf::Vector2f l_position)
	: m_Background(l_size)
{
	m_Inited = false;
	Init(l_size, l_position, 30, sf::Color::Green, sf::Color::White, "Button");
}

Button::Button(const sf::Vector2f l_size, const sf::Vector2f l_position,
	const sf::Color l_button_color, const sf::Color l_text_color,
	const sf::String& l_title, const sf::Uint32 l_text_size)
	: m_Background(l_size)
{
	m_Inited = false;
	Init(l_size, l_position, l_text_size, l_button_color, l_text_color, l_title);
}

void Button::Init(const sf::Vector2f l_size,
	const sf::Vector2f l_position,
	const sf::Uint32 l_text_size,
	const sf::Color l_button_color,
	const sf::Color l_text_color,
	const sf::String& l_text)
{
	this->m_Font.loadFromFile("Assets/Fonts/titillium.otf");

	this->m_Text.setFont(this->m_Font);
	this->m_Text.setString(l_text);
	this->m_Text.setCharacterSize(l_text_size);
	this->m_Text.setFillColor(l_text_color);
	this->m_Text.setPosition(AVMath::GetCenterCoordinates(l_position, l_size, m_Text.getLocalBounds()));

	this->m_Background.setFillColor(l_button_color);
	this->m_Background.setPosition(l_position);
	this->m_Inited = true;
}

void Button::SetSize(const sf::Vector2f l_size)
{
	this->m_Background.setSize(l_size);
	this->m_Text.setPosition(AVMath::GetCenterCoordinates(m_Background.getPosition(), l_size, m_Text.getLocalBounds()));
}

void Button::SetPosition(const sf::Vector2f l_position)
{
	this->m_Background.setPosition(l_position);
	this->m_Text.setPosition(AVMath::GetCenterCoordinates(l_position, m_Background.getSize(), m_Text.getLocalBounds()));
}

void Button::SetFont(const sf::Font& l_font)
{
	this->m_Text.setFont(l_font);
}

void Button::SetTextSize(const sf::Uint32 l_size)
{
	this->m_Text.setCharacterSize(l_size);
}

void Button::SetText(const sf::String& l_text)
{
	this->m_Text.setString(l_text);
	//Experimenting
	this->m_Text.setPosition(AVMath::GetCenterCoordinates(this->m_Background.getPosition(),
		this->m_Background.getSize(), this->m_Text.getLocalBounds()));
}

void Button::SetTextColor(const sf::Color l_color)
{
	this->m_Text.setFillColor(l_color);
}

void Button::SetTextBackgroundColor(const sf::Color l_color)
{
	this->m_Text.setOutlineColor(l_color);
}

void Button::SetTextAlignment(TextAlignment l_alignment)
{
	//TODO(Nuno): Think about how to implement this

	//auto position = utils::Math::getCenterCoordinates();

	//this->m_Text.setPosition(position);
}

void Button::SetBackgroundColor(const sf::Color l_color)
{
	this->m_Background.setFillColor(l_color);
}

void Button::SetBackgroundOutlineColor(const sf::Color l_color)
{
	this->m_Background.setOutlineColor(l_color);
}

void Button::SetBackgroundOutlineThickness(const float l_thickness)
{
	this->m_Background.setOutlineThickness(l_thickness);
}

void Button::Update(float timestep)
{
	if (this->m_Inited)
	{

	}
}

void Button::Render(sf::RenderWindow& l_window)
{
	if (this->m_Inited)
	{
		l_window.draw(this->m_Background);
		l_window.draw(this->m_Text);
	}
}

sf::FloatRect Button::GetGlobalBounds()
{
	return this->m_Background.getGlobalBounds();
}