#include "Healthbar.hpp"

av::ui::Healthbar::Healthbar(const sf::Vector2f l_position)
    : m_current_health_(sf::Vector2f(HP_WIDTH, HP_HEIGHT)), 
    m_missing_health_(sf::Vector2f(0.f, HP_HEIGHT)), m_health_(100)
{
    // Setup current health bar
    this->m_current_health_.setPosition(l_position.x, l_position.y - HP_HEIGHT);
    this->m_current_health_.setFillColor(sf::Color::Green);

    this->m_missing_health_.setFillColor(sf::Color::Red);
}

void av::ui::Healthbar::Update(float timestep) const
{

}

void av::ui::Healthbar::Render(sf::RenderWindow& l_window) const
{
    l_window.draw(this->m_current_health_);
    l_window.draw(this->m_missing_health_);
}

void av::ui::Healthbar::SetPosition(const sf::Vector2f l_position)
{
    this->m_current_health_.setPosition(l_position.x, l_position.y - HP_HEIGHT);
}

bool av::ui::Healthbar::Minus(const sf::Uint32 l_damage)
{
    if (this->m_health_ - static_cast<int>(l_damage) <= 0) {
        return false; // Entity is 'dead'
    }

	const auto current_health_position = sf::Vector2f(static_cast<float>(((this->m_health_-l_damage))*HP_WIDTH/100), HP_HEIGHT);

	this->m_current_health_.setSize(current_health_position);
	this->m_health_ -= l_damage; // Update health to calculate missing health

	const auto missing_health_position = sf::Vector2f(this->m_current_health_.getPosition().x + this->m_current_health_.getSize().x,
	                                            this->m_current_health_.getPosition().y);

	this->m_missing_health_.setPosition(missing_health_position);
	this->m_missing_health_.setSize(sf::Vector2f(HP_WIDTH - this->m_current_health_.getSize().x, HP_HEIGHT));
        
	return true;
}
