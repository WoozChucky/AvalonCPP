//
// Created by Nuno Levezinho on 07/02/2018.
//

#include "MouseCursor.h"

av::MouseCursor::MouseCursor(const float l_scale, const sf::String l_file_location)
{

    if(!m_texture_.loadFromFile(l_file_location))
    {
        throw "Texture load failed"; // this is intended for now
    }

    //NOTE: Does the sprite need a size ?
    this->m_body_.setTexture(this->m_texture_);
    this->m_body_.setScale(l_scale, l_scale);
}

void av::MouseCursor::Render(sf::RenderWindow& l_window) const
{
    l_window.draw(this->m_body_);
}

sf::Vector2f av::MouseCursor::GetCenterPosition() const
{
    return this->m_body_.getPosition();
}

void av::MouseCursor::SetPosition(const sf::Vector2f& l_position)
{
    const auto fixed_position = sf::Vector2f(
            l_position.x - m_body_.getScale().x * (m_body_.getLocalBounds().width / 2),
            l_position.y - m_body_.getScale().y * (m_body_.getLocalBounds().height / 2));

    this->m_body_.setPosition(fixed_position);
}