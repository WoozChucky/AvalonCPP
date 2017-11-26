#include "Button.hpp"
#include "Utils/Math.hpp"


av::ui::Button::Button(const sf::Vector2f l_size, const sf::Vector2f l_position)
	: m_click_callback_(nullptr),
	m_enter_callback_(nullptr), m_exit_callback_(nullptr), m_background_(l_size)
{
	m_inited_ = false;
	Init(l_size, l_position, 30, sf::Color::Green, sf::Color::White, "Button");
}

av::ui::Button::Button(const sf::Vector2f l_size, const sf::Vector2f l_position,
                       const sf::Color l_button_color, const sf::Color l_text_color,
                       const sf::String l_title, const sf::Uint32 l_text_size)
	: m_click_callback_(nullptr),
	m_enter_callback_(nullptr), m_exit_callback_(nullptr), m_background_(l_size)
{
	m_inited_ = false;
	Init(l_size, l_position, l_text_size, l_button_color, l_text_color, l_title);
}

void av::ui::Button::Init(const sf::Vector2f l_size, 
						  const sf::Vector2f l_position,
                          const sf::Uint32 l_text_size, 
						  const sf::Color l_button_color, 
						  const sf::Color l_text_color,
                          const sf::String l_text)
{
	this->m_font_.loadFromFile("Assets/Fonts/titillium.otf");

	this->m_text_.setFont(this->m_font_);
	this->m_text_.setString(l_text);
	this->m_text_.setCharacterSize(l_text_size);
	this->m_text_.setFillColor(l_text_color);
	this->m_text_.setPosition(utils::Math::getCenterCoordinates(l_position, l_size, m_text_.getLocalBounds()));

	this->m_background_.setFillColor(l_button_color);
	this->m_background_.setPosition(l_position);
	this->m_inited_ = true;
}

void av::ui::Button::SetSize(const sf::Vector2f l_size)
{
	this->m_background_.setSize(l_size);
	this->m_text_.setPosition(utils::Math::getCenterCoordinates(m_background_.getPosition(), l_size, m_text_.getLocalBounds()));
}

void av::ui::Button::SetPosition(const sf::Vector2f l_position)
{
	this->m_background_.setPosition(l_position);
	this->m_text_.setPosition(utils::Math::getCenterCoordinates(l_position, m_background_.getSize(), m_text_.getLocalBounds()));
}

void av::ui::Button::SetFont(const sf::Font l_font)
{
	this->m_text_.setFont(l_font);
}

void av::ui::Button::SetTextSize(const sf::Uint32 l_size)
{
	this->m_text_.setCharacterSize(l_size);
}

void av::ui::Button::SetText(const sf::String l_text)
{
	this->m_text_.setString(l_text);
	//Experimenting
	this->m_text_.setPosition(utils::Math::getCenterCoordinates(this->m_background_.getPosition(), 
		this->m_background_.getSize(), this->m_text_.getLocalBounds()));
}

void av::ui::Button::SetTextColor(const sf::Color l_color)
{
	this->m_text_.setFillColor(l_color);
}

void av::ui::Button::SetTextBackgroundColor(const sf::Color l_color)
{
	this->m_text_.setOutlineColor(l_color);
}

void av::ui::Button::SetTextAlignment(enums::TextAlignment l_alignment)
{
	//TODO(Nuno): Think about how to implement this
	
	//auto position = utils::Math::getCenterCoordinates();

	//this->m_text_.setPosition(position);
}

void av::ui::Button::SetBackgroundColor(const sf::Color l_color)
{
	this->m_background_.setFillColor(l_color);
}

void av::ui::Button::SetBackgroundOutlineColor(const sf::Color l_color)
{
	this->m_background_.setOutlineColor(l_color);
}

void av::ui::Button::SetBackgroundOutlineThickness(const float l_tickness)
{
	this->m_background_.setOutlineThickness(l_tickness);
}

void av::ui::Button::SetOnClick(events::MouseClickCallback* l_callback)
{
	this->m_click_callback_ = l_callback;
}

void av::ui::Button::SetOnMouseEnter(events::MouseOverEnterCallback* l_callback)
{
	this->m_enter_callback_ = l_callback;
}

void av::ui::Button::SetOnMouseExit(events::MouseOverExitCallback* l_callback)
{
	this->m_exit_callback_ = l_callback;
}

void av::ui::Button::OnClick() const
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
	if(this->m_inited_)
	{
		
	}
}

void av::ui::Button::Render(sf::RenderWindow& l_window)
{
	if(this->m_inited_)
	{
		l_window.draw(this->m_background_);
		l_window.draw(this->m_text_);
	}
}

sf::FloatRect av::ui::Button::GetGlobalBounds()
{
	return this->m_background_.getGlobalBounds();
}


