#include "PlayerGraphicsComponent.hpp"
#include "../Entities/Player.hpp"

av::PlayerGraphicsComponent::PlayerGraphicsComponent()
{

}

void av::PlayerGraphicsComponent::Render(av::Entity& l_entity, sf::RenderWindow& l_window)
{
    auto player = static_cast<av::Player&>(l_entity);

    l_window.draw(player);
	l_window.draw(player.m_rifle_);
	for (auto i = 0; i < player.m_bullets.size(); i++) {
		l_window.draw(player.m_bullets[i]);
	}

    
}